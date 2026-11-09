// ======================================================================
// \title  Processor.cpp
// \brief  cpp file for the FixedMessageLimit::Processor component
// ======================================================================

#include "FixedMessageLimit/Processor/Processor.hpp"

#include "Fw/Time/TimeInterval.hpp"
#include "Fw/Types/Assert.hpp"
#include "Os/Task.hpp"

namespace FixedMessageLimit {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Processor::Processor(const char* const compName)
    : ProcessorComponentBase(compName),
      m_pending(0),
      m_ticksSkipped(0),
      m_ticksAdmitted(0),
      m_ticksProcessed(0),
      m_processingTimeMs(0) {}

Processor::~Processor() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Processor::schedIn_handler(FwIndexType portNum, U32 context) {
    // Claim a slot first, then check whether the claim was within the limit. A message is queued only
    // when fewer than MAX_PENDING slots were claimed before this one, so the queue never holds more than
    // MAX_PENDING schedInInternal messages. Concurrent callers may push the counter above MAX_PENDING
    // momentarily, which can only cause a spurious skip, never an extra message.
    const FwSizeType previous = this->m_pending.fetch_add(1);
    if (previous < FixedMessageLimit::MAX_PENDING) {
        this->m_ticksAdmitted.fetch_add(1);
        this->schedInInternal_internalInterfaceInvoke();
    } else {
        // Over the limit: give the slot back and skip this tick
        this->m_pending.fetch_sub(1);
        this->m_ticksSkipped.fetch_add(1);
        this->log_WARNING_LO_TickSkipped(static_cast<U32>(previous));
    }
}

// ----------------------------------------------------------------------
// Handler implementations for internal ports
// ----------------------------------------------------------------------

void Processor::schedInInternal_overflowHook() {
    // The message was rejected by a full queue: release the slot so the next tick can retry
    FW_ASSERT(this->m_pending > 0);
    this->m_pending.fetch_sub(1);
    this->m_ticksSkipped.fetch_add(1);
    this->log_WARNING_LO_TickOverflow();
}

void Processor::schedInInternal_internalInterfaceHandler() {
    // Release the slot before doing the work: a tick arriving during the work may claim it
    FW_ASSERT(this->m_pending > 0);
    this->m_pending.fetch_sub(1);

    // DEMONSTRATION ONLY: sleeping on the component thread is how this example makes the component fall
    // behind its rate group on demand, so that the limit and the TickSkipped event can be observed from
    // the ground. Flight components must never block their thread like this; the work done here stands
    // in for a bounded unit of real processing.
    if (this->m_processingTimeMs > 0) {
        const U32 seconds = this->m_processingTimeMs / 1000;
        const U32 microseconds = (this->m_processingTimeMs % 1000) * 1000;
        (void)Os::Task::delay(Fw::TimeInterval(seconds, microseconds));
    }

    this->m_ticksProcessed++;
    this->tlmWrite_TicksProcessed(this->m_ticksProcessed);
    this->tlmWrite_TicksAdmitted(this->m_ticksAdmitted.load());
    this->tlmWrite_TicksSkipped(this->m_ticksSkipped.load());
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void Processor::SET_PROCESSING_TIME_cmdHandler(FwOpcodeType opCode, U32 cmdSeq, U32 milliseconds) {
    if (milliseconds > FixedMessageLimit::MAX_PROCESSING_TIME_MS) {
        this->log_WARNING_LO_ProcessingTimeInvalid(milliseconds, FixedMessageLimit::MAX_PROCESSING_TIME_MS);
        this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::VALIDATION_ERROR);
        return;
    }
    this->m_processingTimeMs = milliseconds;
    // A new processing time starts a new observation window: let the throttled skip events fire again
    this->log_WARNING_LO_TickSkipped_ThrottleClear();
    this->log_WARNING_LO_TickOverflow_ThrottleClear();
    this->log_ACTIVITY_LO_ProcessingTimeSet(milliseconds);
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}

}  // namespace FixedMessageLimit
