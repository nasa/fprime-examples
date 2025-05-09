// ======================================================================
// \title  DecafFramer.cpp
// \author thomas-bc
// \brief  cpp file for DecafFramer component implementation class
// ======================================================================

#include "CustomFraming/DecafFramer/DecafFramer.hpp"
#include "CustomFraming/Types/FrameHeaderSerializableAc.hpp"
#include "CustomFraming/Types/FrameTrailerSerializableAc.hpp"
#include "Utils/Hash/Hash.hpp"

namespace CustomFraming {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

DecafFramer ::DecafFramer(const char* const compName) : DecafFramerComponentBase(compName) {}

DecafFramer ::~DecafFramer() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void DecafFramer ::dataIn_handler(FwIndexType portNum, Fw::Buffer& data, const ComCfg::FrameContext& context) {
    CustomFraming::Types::FrameHeader header;
    CustomFraming::Types::FrameTrailer trailer;

    // Full size of the frame will be size of header + data + trailer
    FwSizeType frameSize =
        CustomFraming::Types::FrameHeader::SERIALIZED_SIZE + data.getSize() + CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE;
    FW_ASSERT(data.getSize() <= std::numeric_limits<CustomFraming::Types::TokenType>::max(), static_cast<FwAssertArgType>(frameSize));
    FW_ASSERT(frameSize <= std::numeric_limits<Fw::Buffer::SizeType>::max(), static_cast<FwAssertArgType>(frameSize));

    // Allocate frame buffer
    Fw::Buffer frameBuffer = this->bufferAllocate_out(0, static_cast<Fw::Buffer::SizeType>(frameSize));
    auto frameSerializer = frameBuffer.getSerializer();
    Fw::SerializeStatus status;

    // Serialize the header
    // 0xDECAF000 is already set as the default value for the header startWord field in the FPP type definition
    header.setlengthField(data.getSize());
    status = frameSerializer.serialize(header);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    // Serialize the data
    status = frameSerializer.serialize(data.getData(), data.getSize(), Fw::Serialization::OMIT_LENGTH);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    // Serialize the trailer (with CRC computation)
    Utils::HashBuffer hashBuffer;
    Utils::Hash::hash(frameBuffer.getData(), frameSize - HASH_DIGEST_LENGTH, hashBuffer);
    trailer.setcrcField(hashBuffer.asBigEndianU32());
    status = frameSerializer.serialize(trailer);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);

    // Send the full frame out - this port shall always be connected
    this->dataOut_out(0, frameBuffer, context);
    // Return original (unframed) data buffer ownership back to its sender - always connected
    this->dataReturnOut_out(0, data, context);
}

void DecafFramer ::comStatusIn_handler(FwIndexType portNum, Fw::Success& condition) {
    if (this->isConnected_comStatusOut_OutputPort(portNum)) {
        this->comStatusOut_out(portNum, condition);
    }
}

void DecafFramer ::dataReturnIn_handler(FwIndexType portNum, Fw::Buffer& frameBuffer, const ComCfg::FrameContext& context) {
    // dataReturnIn is the allocated buffer coming back from the ComManager (e.g. ComStub) component
    this->bufferDeallocate_out(0, frameBuffer);
}

}  // namespace CustomFraming
