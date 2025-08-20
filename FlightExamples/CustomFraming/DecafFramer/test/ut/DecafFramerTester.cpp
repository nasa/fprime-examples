// ======================================================================
// \title  DecafFramerTester.cpp
// \author thomas-bc
// \brief  cpp file for DecafFramer component test harness implementation class
// ======================================================================

#include "DecafFramerTester.hpp"
#include "CustomFraming/Types/FrameHeaderSerializableAc.hpp"
#include "CustomFraming/Types/FrameTrailerSerializableAc.hpp"

namespace CustomFraming {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

DecafFramerTester ::DecafFramerTester()
    : DecafFramerGTestBase("DecafFramerTester", DecafFramerTester::MAX_HISTORY_SIZE), component("DecafFramer") {
    this->initComponents();
    this->connectPorts();
}

DecafFramerTester ::~DecafFramerTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void DecafFramerTester ::testFrameDeallocation() {
    // When receiving a buffer on dataReturnIn, the buffer should be deallocated
    Fw::Buffer buffer;
    ComCfg::FrameContext context;
    this->invoke_to_dataReturnIn(0, buffer, context);
    ASSERT_from_bufferDeallocate_SIZE(1);
    ASSERT_from_bufferDeallocate(0, buffer);
}

void DecafFramerTester ::testComStatusPassThrough() {
    // Send a status message to the component
    Fw::Success inputStatus = Fw::Success::SUCCESS;
    this->invoke_to_comStatusIn(0, inputStatus);
    ASSERT_from_comStatusOut_SIZE(1);
    ASSERT_from_comStatusOut(0, inputStatus);  // at index 0, received SUCCESS
    inputStatus = Fw::Success::FAILURE;
    this->invoke_to_comStatusIn(0, inputStatus);
    ASSERT_from_comStatusOut_SIZE(2);
    ASSERT_from_comStatusOut(1, inputStatus);  // at index 1, received FAILURE
}

void DecafFramerTester ::testNominalFraming() {
    U8 bufferData[100];
    Fw::Buffer buffer(bufferData, sizeof(bufferData));
    ComCfg::FrameContext context;

    // Fill the buffer with some data
    for (U32 i = 0; i < sizeof(bufferData); ++i) {
        bufferData[i] = static_cast<U8>(i);
    }

    // Send the buffer to the component
    this->invoke_to_dataIn(0, buffer, context);
    ASSERT_from_dataOut_SIZE(1);        // One frame emitted
    ASSERT_from_dataReturnOut_SIZE(1);  // Original data buffer ownership returned

    Fw::Buffer outputBuffer = this->fromPortHistory_dataOut->at(0).data;
    // Check the size of the output buffer
    ASSERT_EQ(outputBuffer.getSize(),
              sizeof(bufferData) + Types::FrameHeader::SERIALIZED_SIZE + Types::FrameTrailer::SERIALIZED_SIZE);
    // Check header
    Types::FrameHeader defaultHeader;
    Types::FrameHeader outputHeader;
    outputBuffer.getDeserializer().deserializeTo(outputHeader);
    ASSERT_EQ(outputHeader.get_startWord(), defaultHeader.get_startWord());
    ASSERT_EQ(outputHeader.get_lengthField(), sizeof(bufferData));
    // Check data
    for (U32 i = 0; i < sizeof(bufferData); ++i) {
        ASSERT_EQ(outputBuffer.getData()[i + Types::FrameHeader::SERIALIZED_SIZE], bufferData[i]);
    }
}

// ----------------------------------------------------------------------
// Test Harness: Handler implementations for output ports
// ----------------------------------------------------------------------

Fw::Buffer DecafFramerTester::from_bufferAllocate_handler(FwIndexType portNum, FwSizeType size) {
    this->pushFromPortEntry_bufferAllocate(size);
    this->m_buffer.setData(this->m_buffer_slot);
    this->m_buffer.setSize(size);
    ::memset(this->m_buffer.getData(), 0, size);
    return this->m_buffer;
}

}  // namespace CustomFraming
