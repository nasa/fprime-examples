// ======================================================================
// \title  WorkerTester.cpp
// \author mstarch
// \brief  cpp file for Worker component test harness implementation class
// ======================================================================

#include "WorkerTester.hpp"
#include "Fw/Test/UnitTest.hpp"

namespace ManagerWorker {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

WorkerTester ::WorkerTester() : WorkerGTestBase("WorkerTester", WorkerTester::MAX_HISTORY_SIZE), component("Worker") {
    this->initComponents();
    this->connectPorts();
}

WorkerTester ::~WorkerTester() {
   this->component.deinit();
}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void WorkerTester ::test_start_done() {
    REQUIREMENT("MANAGER-WORKER-WORKER-001");
    // Test that a start work invocation results in a worker start call
    this->invoke_to_startWork(0);
    this->component.doDispatch();
    REQUIREMENT("MANAGER-WORKER-WORKER-003");
    ASSERT_from_workDone_SIZE(1);
}

}  // namespace ManagerWorker
