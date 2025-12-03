// ======================================================================
// \title  ManagerTester.cpp
// \author mstarch
// \brief  cpp file for Manager component test harness implementation class
// ======================================================================

#include "ManagerTester.hpp"
#include "Fw/Test/UnitTest.hpp"

namespace ManagerWorker {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

ManagerTester ::ManagerTester()
    : ManagerGTestBase("ManagerTester", ManagerTester::MAX_HISTORY_SIZE), component("Manager") {
    this->initComponents();
    this->connectPorts();
}

ManagerTester ::~ManagerTester() {
    this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ManagerTester ::test_start_work() {
    REQUIREMENT("MANAGER-WORKER-MANAGER-001");
    // Test that a start work invocation results in a worker start call
    this->sendCmd_START(0, 0);
    this->component.doDispatch();
    ASSERT_from_startWorker_SIZE(1);
    REQUIREMENT("MANAGER-WORKER-MANAGER-003");
    ASSERT_EVENTS_StartWork_SIZE(1);
}

void ManagerTester ::test_cancel_work() {
    REQUIREMENT("MANAGER-WORKER-MANAGER-002");
    // Prepare for a cancel
    this->sendCmd_START(0, 0);
    this->component.doDispatch();
    ASSERT_from_startWorker_SIZE(1);
    // Test that a cancel work invocation results in a worker cancel call
    this->sendCmd_STOP(0, 0);
    this->component.doDispatch();
    ASSERT_from_cancelWorker_SIZE(1);
    ASSERT_EVENTS_WorkerCanceled_SIZE(0);
    // Test that the worker cancel response results in a worker canceled event
    this->invoke_to_doneRecv(0, Fw::Completed::CANCELED);
    this->component.doDispatch();
    ASSERT_EVENTS_WorkerCanceled_SIZE(1);
}

void ManagerTester ::test_done_work() {
    REQUIREMENT("MANAGER-WORKER-MANAGER-004");
    // Prepare for a done
    this->sendCmd_START(0, 0);
    this->component.doDispatch();
    ASSERT_from_startWorker_SIZE(1);

    // Test that the worker done response results in a worker done event
    this->invoke_to_doneRecv(0, Fw::Completed::COMPLETED);
    this->component.doDispatch();
    ASSERT_EVENTS_WorkerDone_SIZE(1);
}


void ManagerTester ::test_responsiveness() {
    REQUIREMENT("MANAGER-WORKER-MANAGER-005");
    // Prepare for testing for responsiveness
    this->sendCmd_START(0, 0);
    this->component.doDispatch();
    ASSERT_from_startWorker_SIZE(1);

    // Test the manager remains responsive
    this->invoke_to_pingIn(0, 123);
    this->component.doDispatch();
    ASSERT_from_pingOut_SIZE(1);
    ASSERT_from_pingOut(0, 123);
    // Check responsiveness of the busy call
    REQUIREMENT("MANAGER-WORKER-MANAGER-006");
    this->sendCmd_START(0, 0);
    this->component.doDispatch();
    ASSERT_EVENTS_WorkerBusy_SIZE(1);
}

}  // namespace ManagerWorker
