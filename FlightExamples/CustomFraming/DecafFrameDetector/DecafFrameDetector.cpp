// ======================================================================
// \title  DecafFrameDetector.hpp
// \author thomas-bc
// \brief  hpp file for fprime frame detector definitions
// ======================================================================

#include "CustomFraming/DecafFrameDetector/DecafFrameDetector.hpp"
#include "CustomFraming/Types/FrameHeaderSerializableAc.hpp"
#include "CustomFraming/Types/FrameTrailerSerializableAc.hpp"

namespace CustomFraming {

Svc::FrameDetector::Status DecafFrameDetector::detect(const ::Types::CircularBuffer& data, FwSizeType& size_out) const {
    // If not enough data for header + trailer, report MORE_DATA_NEEDED
    if (data.get_allocated_size() <
        CustomFraming::Types::FrameHeader::SERIALIZED_SIZE + CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE) {
        size_out =
            CustomFraming::Types::FrameHeader::SERIALIZED_SIZE + CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE;
        return Svc::FrameDetector::MORE_DATA_NEEDED;
    }

    CustomFraming::Types::FrameHeader header;
    CustomFraming::Types::FrameTrailer trailer;

    // ---------------- Frame Header ----------------
    // Copy CircularBuffer data into linear buffer, for serialization into FrameHeader object
    U8 header_data[CustomFraming::Types::FrameHeader::SERIALIZED_SIZE];
    Fw::SerializeStatus status = data.peek(header_data, CustomFraming::Types::FrameHeader::SERIALIZED_SIZE, 0);
    if (status != Fw::FW_SERIALIZE_OK) {
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }
    Fw::ExternalSerializeBuffer header_ser_buffer(header_data, CustomFraming::Types::FrameHeader::SERIALIZED_SIZE);
    status = header_ser_buffer.setBuffLen(CustomFraming::Types::FrameHeader::SERIALIZED_SIZE);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(status));
    // Attempt to deserialize data into the FrameHeader object
    status = header.deserializeFrom(header_ser_buffer);
    if (status != Fw::FW_SERIALIZE_OK) {
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }
    // Check that deserialized start_word token matches expected value (default start_word value in the FPP object)
    CustomFraming::Types::FrameHeader default_value;
    if (header.get_startWord() != default_value.get_startWord()) {
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }
    // We expect the frame size to be size of header + body (of size specified in header) + trailer
    const FwSizeType expected_frame_size = CustomFraming::Types::FrameHeader::SERIALIZED_SIZE +
                                           header.get_lengthField() +
                                           CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE;
    // If the current allocated size can't hold the expected_frame_size -> MORE_DATA_NEEDED
    if (data.get_allocated_size() < expected_frame_size) {
        size_out = expected_frame_size;
        return Svc::FrameDetector::MORE_DATA_NEEDED;
    }

    // ---------------- Frame Trailer ----------------
    U8 trailer_data[CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE];
    Fw::ExternalSerializeBuffer trailer_ser_buffer(trailer_data, CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE);
    status = data.peek(trailer_data, CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE,
                       CustomFraming::Types::FrameHeader::SERIALIZED_SIZE + header.get_lengthField());
    if (status != Fw::FW_SERIALIZE_OK) {
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }
    status = trailer_ser_buffer.setBuffLen(CustomFraming::Types::FrameTrailer::SERIALIZED_SIZE);
    FW_ASSERT(status == Fw::FW_SERIALIZE_OK, static_cast<FwAssertArgType>(status));
    // Deserialize trailer from circular buffer (peeked data) into trailer object
    status = trailer.deserializeFrom(trailer_ser_buffer);
    if (status != Fw::FW_SERIALIZE_OK) {
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }

    Utils::Hash hash;
    Utils::HashBuffer hashBuffer;
    // Compute CRC over the transmitted data (header + body)
    FwSizeType hash_field_size = header.get_lengthField() + CustomFraming::Types::FrameHeader::SERIALIZED_SIZE;
    hash.init();
    for (U32 i = 0; i < hash_field_size; i++) {
        U8 byte = 0;
        status = data.peek(byte, i);
        FW_ASSERT(status == Fw::FW_SERIALIZE_OK, status);
        hash.update(&byte, 1);
    }
    hash.finalize(hashBuffer);

    // Compare the transmitted CRC with the computed one
    if (trailer.get_crcField() != hashBuffer.asBigEndianU32()) {
        // CRC mismatch - there likely was data corruption. The protocol
        // being very simple, we don't have a way to recover from this.
        // So we report NO_FRAME_DETECTED and drop the frame
        return Svc::FrameDetector::NO_FRAME_DETECTED;
    }
    // All checks passed - we have detected a frame of size expected_frame_size
    size_out = expected_frame_size;
    return Svc::FrameDetector::FRAME_DETECTED;
}

}  // namespace CustomFraming
