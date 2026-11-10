// ======================================================================
// \title  Processor.hpp
// \brief  hpp file for the FixedMessageLimit::Processor component
//
// Demonstrates the fixed message limit pattern: a sync rate group input
// admits at most FixedMessageLimit::MAX_PENDING messages onto the
// component queue, releasing each slot when the message is dequeued or
// when the queue rejects it.
// ======================================================================

#ifndef FixedMessageLimit_Processor_HPP
#define FixedMessageLimit_Processor_HPP

#include <atomic>

#include "FixedMessageLimit/Processor/FppConstantsAc.hpp"
#include "FixedMessageLimit/Processor/ProcessorComponentAc.hpp"

namespace FixedMessageLimit {

class Processor final : public ProcessorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Processor object
    Processor(const char* const compName  //!< The component name
    );

    //! Destroy Processor object
    ~Processor();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler for schedIn: runs on the rate group thread, claims a slot and queues one schedInInternal message
    void schedIn_handler(FwIndexType portNum,  //!< The port number
                         U32 context           //!< The call order
                         ) override;

    // ----------------------------------------------------------------------
    // Handler implementations for internal ports
    // ----------------------------------------------------------------------

    //! Handler for schedInInternal: runs on the component thread, releases the slot and processes one tick
    void schedInInternal_internalInterfaceHandler() override;

    //! Overflow hook for schedInInternal: runs on the rate group thread when the queue is full, releases the slot
    void schedInInternal_overflowHook() override;

    // ----------------------------------------------------------------------
    // Handler implementations for commands
    // ----------------------------------------------------------------------

    //! Handler for command SET_PROCESSING_TIME
    void SET_PROCESSING_TIME_cmdHandler(FwOpcodeType opCode,  //!< The opcode
                                        U32 cmdSeq,           //!< The command sequence number
                                        U32 milliseconds      //!< Time spent processing each tick
                                        ) override;

    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! Number of schedInInternal messages claimed and not yet dequeued. Shared between the rate group
    //! thread (schedIn_handler, schedInInternal_overflowHook) and the component thread.
    std::atomic<FwSizeType> m_pending;

    //! Number of ticks skipped at the limit or on a full queue. Incremented on the rate group thread,
    //! reported on the component thread.
    std::atomic<U32> m_ticksSkipped;

    //! Number of ticks admitted onto the queue. Incremented on the rate group thread, reported on the
    //! component thread.
    std::atomic<U32> m_ticksAdmitted;

    //! Number of ticks processed. Component thread only.
    U32 m_ticksProcessed;

    //! Simulated per-tick processing time in milliseconds. Component thread only.
    U32 m_processingTimeMs;
};

}  // namespace FixedMessageLimit

#endif
