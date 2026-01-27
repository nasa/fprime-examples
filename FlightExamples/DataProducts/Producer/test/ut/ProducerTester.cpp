// ======================================================================
// \title  ProducerTester.cpp
// \author mstarch
// \brief  cpp file for Producer component test harness implementation class
// ======================================================================

#include "ProducerTester.hpp"

namespace DataProducts {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

ProducerTester ::ProducerTester()
    : ProducerGTestBase("ProducerTester", ProducerTester::MAX_HISTORY_SIZE), component("Producer") {
    this->initComponents();
    this->connectPorts();
}

ProducerTester ::~ProducerTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ProducerTester ::test_data_product_generation() {
    // Test 1: First call to run should allocate a container
    this->clearHistory();
    
    // Invoke run handler for the first time (call 1)
    this->invoke_to_run(0, 0);
    
    // Verify that productGetOut was called once (container allocation request)
    ASSERT_EVENTS_DpMemoryFailure_SIZE(0);
    ASSERT_PRODUCT_GET_SIZE(1);
    ASSERT_PRODUCT_SEND_SIZE(0);

    // Test 2: On 100th call, container should be sent
    this->clearHistory();
    
    // Run 99 more times (calls 2-100) to fill the container
    for (U32 i = 1; i < 100; ++i) {
        ASSERT_PRODUCT_SEND_SIZE(0);
        this->invoke_to_run(0, 0);
    }
    // Only after the 100th call should the container be sent, no new allocations yet
    ASSERT_PRODUCT_SEND_SIZE(1);
    ASSERT_PRODUCT_GET_SIZE(0);

    // Test 3: On 101st call, new container should be allocated again
    this->clearHistory();
    ASSERT_PRODUCT_GET_SIZE(0);
    // Call 101 (first call after the send on call 100)
    this->invoke_to_run(0, 0);
    ASSERT_PRODUCT_GET_SIZE(1);

    // Test 4: On 200th call, second container should be sent
    this->clearHistory();
    
    // Run 99 more times (calls 102-200) to fill the second container
    for (U32 i = 1; i < 100; ++i) {
        ASSERT_PRODUCT_SEND_SIZE(0);
        this->invoke_to_run(0, 0);
    }
    // Another send should have occurred on the 200th call
    ASSERT_PRODUCT_SEND_SIZE(1);
    ASSERT_PRODUCT_GET_SIZE(0);
}


void ProducerTester ::test_data_failed_allocate() {
    this->m_allocation_failure = true;
    this->clearHistory();
    
    // Invoke run handler for the first time (call 1)
    for (U32 i = 0; i < 200; i++) {
        this->invoke_to_run(0, 0);
        ASSERT_EVENTS_DpMemoryFailure_SIZE(FW_MIN(i + 1, 2));
    }
    ASSERT_PRODUCT_SEND_SIZE(0);
}

Fw::Success::T ProducerTester ::productGet_handler(FwDpIdType id, FwSizeType dataSize, Fw::Buffer& buffer) {
    EXPECT_EQ(dataSize, sizeof(this->m_buffer));
    buffer.set(this->m_buffer, dataSize);
    this->pushProductGetEntry(id, dataSize);
    return (this->m_allocation_failure) ? Fw::Success::FAILURE : Fw::Success::SUCCESS;
}

}  // namespace DataProducts
