// ======================================================================
// \title  ProcessorTester.cpp
// \brief  cpp file for Processor component test harness implementation class
// ======================================================================

#include "ProcessorTester.hpp"

namespace FixedMessageLimit {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

ProcessorTester::ProcessorTester()
    : ProcessorGTestBase("ProcessorTester", ProcessorTester::MAX_HISTORY_SIZE), component("Processor") {
    this->initComponents();
    this->connectPorts();
}

ProcessorTester::~ProcessorTester() {
    this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ProcessorTester::test_ticks_within_limit() {
    // Each of MAX_PENDING ticks is queued and processed exactly once
    this->tick(FixedMessageLimit::MAX_PENDING);
    this->dispatch(FixedMessageLimit::MAX_PENDING);

    ASSERT_TLM_TicksProcessed_SIZE(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksAdmitted(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksSkipped(FixedMessageLimit::MAX_PENDING - 1, 0);
    ASSERT_EVENTS_SIZE(0);
}

void ProcessorTester::test_ticks_beyond_limit_skipped() {
    const FwSizeType extra = 2;
    // Ticks beyond MAX_PENDING are skipped on the caller's thread with an event each
    this->tick(FixedMessageLimit::MAX_PENDING + extra);
    ASSERT_EVENTS_SIZE(extra);
    ASSERT_EVENTS_TickSkipped_SIZE(extra);
    for (FwSizeType i = 0; i < extra; i++) {
        ASSERT_EVENTS_TickSkipped(i, FixedMessageLimit::MAX_PENDING);
    }

    // Exactly MAX_PENDING messages were queued: dispatching that many drains the queue (one more would block)
    this->dispatch(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed_SIZE(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksAdmitted(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksSkipped(FixedMessageLimit::MAX_PENDING - 1, extra);
}

void ProcessorTester::test_slot_released_after_dispatch() {
    // Fill every slot, then dispatch one message: the slot it held is released
    this->tick(FixedMessageLimit::MAX_PENDING);
    this->dispatch(1);
    ASSERT_TLM_TicksProcessed_SIZE(1);

    // One more tick is admitted into the released slot; a second is skipped
    this->tick(2);
    ASSERT_EVENTS_TickSkipped_SIZE(1);

    // MAX_PENDING messages remain on the queue
    this->dispatch(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed_SIZE(FixedMessageLimit::MAX_PENDING + 1);
    ASSERT_TLM_TicksProcessed(FixedMessageLimit::MAX_PENDING, FixedMessageLimit::MAX_PENDING + 1);
    ASSERT_TLM_TicksAdmitted(FixedMessageLimit::MAX_PENDING, FixedMessageLimit::MAX_PENDING + 1);
    ASSERT_TLM_TicksSkipped(FixedMessageLimit::MAX_PENDING, 1);
}

void ProcessorTester::test_overflow_releases_slot() {
    // Fill the component queue with commands so that the next internal message is rejected
    for (FwSizeType i = 0; i < ProcessorTester::TEST_INSTANCE_QUEUE_DEPTH; i++) {
        this->sendCmd_SET_PROCESSING_TIME(0, static_cast<U32>(i), 0);
    }

    // The tick is admitted (slot claimed) but the queue is full: the overflow hook releases the slot
    this->tick(1);
    ASSERT_EVENTS_SIZE(1);
    ASSERT_EVENTS_TickOverflow_SIZE(1);
    ASSERT_EVENTS_TickSkipped_SIZE(0);

    // Drain the commands
    this->clearHistory();
    this->dispatch(ProcessorTester::TEST_INSTANCE_QUEUE_DEPTH);
    ASSERT_CMD_RESPONSE_SIZE(ProcessorTester::TEST_INSTANCE_QUEUE_DEPTH);

    // Every slot is available again: MAX_PENDING ticks queue and process, none are skipped
    this->tick(FixedMessageLimit::MAX_PENDING);
    ASSERT_EVENTS_TickSkipped_SIZE(0);
    this->dispatch(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed_SIZE(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksProcessed(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING);
    // Admitted counts the overflowed tick as well; skipped counts it once
    ASSERT_TLM_TicksAdmitted(FixedMessageLimit::MAX_PENDING - 1, FixedMessageLimit::MAX_PENDING + 1);
    ASSERT_TLM_TicksSkipped(FixedMessageLimit::MAX_PENDING - 1, 1);
}

void ProcessorTester::test_set_processing_time() {
    // Maximum value is accepted
    this->sendCmd_SET_PROCESSING_TIME(0, 1, FixedMessageLimit::MAX_PROCESSING_TIME_MS);
    this->dispatch(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, Processor::OPCODE_SET_PROCESSING_TIME, 1, Fw::CmdResponse::OK);
    ASSERT_EVENTS_ProcessingTimeSet_SIZE(1);
    ASSERT_EVENTS_ProcessingTimeSet(0, FixedMessageLimit::MAX_PROCESSING_TIME_MS);

    // One past the maximum is rejected and leaves the setting unchanged
    this->clearHistory();
    this->sendCmd_SET_PROCESSING_TIME(0, 2, FixedMessageLimit::MAX_PROCESSING_TIME_MS + 1);
    this->dispatch(1);
    ASSERT_CMD_RESPONSE_SIZE(1);
    ASSERT_CMD_RESPONSE(0, Processor::OPCODE_SET_PROCESSING_TIME, 2, Fw::CmdResponse::VALIDATION_ERROR);
    ASSERT_EVENTS_ProcessingTimeInvalid_SIZE(1);
    ASSERT_EVENTS_ProcessingTimeInvalid(0, FixedMessageLimit::MAX_PROCESSING_TIME_MS + 1,
                                        FixedMessageLimit::MAX_PROCESSING_TIME_MS);
    ASSERT_EVENTS_ProcessingTimeSet_SIZE(0);

    // A small delay is applied to tick processing without affecting the tick accounting
    this->clearHistory();
    this->sendCmd_SET_PROCESSING_TIME(0, 3, 1);
    this->dispatch(1);
    ASSERT_CMD_RESPONSE(0, Processor::OPCODE_SET_PROCESSING_TIME, 3, Fw::CmdResponse::OK);
    this->tick(1);
    this->dispatch(1);
    ASSERT_TLM_TicksProcessed_SIZE(1);
    ASSERT_TLM_TicksProcessed(0, 1);
}

void ProcessorTester::test_skip_event_throttle() {
    // Skips beyond the throttle emit no further TickSkipped events
    const FwSizeType skips = Processor::EVENTID_TICKSKIPPED_THROTTLE + 2;
    this->tick(FixedMessageLimit::MAX_PENDING + skips);
    ASSERT_EVENTS_TickSkipped_SIZE(Processor::EVENTID_TICKSKIPPED_THROTTLE);
    this->dispatch(FixedMessageLimit::MAX_PENDING);
    ASSERT_TLM_TicksSkipped(FixedMessageLimit::MAX_PENDING - 1, static_cast<U32>(skips));
    // Setting a processing time clears the throttle so the next skip is reported again
    this->clearHistory();
    this->sendCmd_SET_PROCESSING_TIME(0, 1, 0);
    this->dispatch(1);
    ASSERT_CMD_RESPONSE(0, Processor::OPCODE_SET_PROCESSING_TIME, 1, Fw::CmdResponse::OK);
    this->tick(FixedMessageLimit::MAX_PENDING + 1);
    ASSERT_EVENTS_TickSkipped_SIZE(1);
    ASSERT_EVENTS_TickSkipped(0, FixedMessageLimit::MAX_PENDING);
    this->dispatch(FixedMessageLimit::MAX_PENDING);
}

// ----------------------------------------------------------------------
// Helper functions
// ----------------------------------------------------------------------

void ProcessorTester::tick(FwSizeType count) {
    for (FwSizeType i = 0; i < count; i++) {
        this->invoke_to_schedIn(0, static_cast<U32>(i));
    }
}

void ProcessorTester::dispatch(FwSizeType count) {
    for (FwSizeType i = 0; i < count; i++) {
        this->component.doDispatch();
    }
}

}  // namespace FixedMessageLimit
