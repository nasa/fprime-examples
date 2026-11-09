// ======================================================================
// \title  ProcessorTester.hpp
// \brief  hpp file for Processor component test harness implementation class
// ======================================================================

#ifndef FixedMessageLimit_ProcessorTester_HPP
#define FixedMessageLimit_ProcessorTester_HPP

#include "FixedMessageLimit/Processor/Processor.hpp"
#include "FixedMessageLimit/Processor/ProcessorGTestBase.hpp"

namespace FixedMessageLimit {

class ProcessorTester : public ProcessorGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 50;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

    // Queue depth supplied to the component instance under test
    static const FwSizeType TEST_INSTANCE_QUEUE_DEPTH = 10;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object ProcessorTester
    ProcessorTester();

    //! Destroy object ProcessorTester
    ~ProcessorTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test: each tick within the limit is queued and processed once
    void test_ticks_within_limit();

    //! Test: ticks beyond MAX_PENDING are skipped and counted
    void test_ticks_beyond_limit_skipped();

    //! Test: a dequeued tick releases its slot for a later tick
    void test_slot_released_after_dispatch();

    //! Test: a tick rejected by a full queue releases its slot
    void test_overflow_releases_slot();

    //! Test: SET_PROCESSING_TIME accepts values up to the maximum and rejects larger ones
    void test_set_processing_time();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Invoke schedIn count times without dispatching
    void tick(FwSizeType count);

    //! Dispatch count messages from the component queue
    void dispatch(FwSizeType count);

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Processor component;
};

}  // namespace FixedMessageLimit

#endif
