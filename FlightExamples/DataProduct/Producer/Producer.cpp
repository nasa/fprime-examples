// ======================================================================
// \title  Producer.cpp
// \author mstarch
// \brief  cpp file for Producer component implementation class
// ======================================================================

#include "DataProduct/Producer/Producer.hpp"
#include <cmath>

namespace DataProduct {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

Producer ::Producer(const char* const compName)
    : ProducerComponentBase(compName), m_count(0), m_container(), m_containerValid(false) {}

Producer ::~Producer() {}

// ----------------------------------------------------------------------
// Handler implementations for typed input ports
// ----------------------------------------------------------------------

void Producer ::run_handler(FwIndexType portNum, U32 context) {
    if (not this->m_containerValid) {
        // Record count * size of each record * 2 record types
        const FwSizeType containerSize = RECORD_COUNT * (SinusoidRecordType::SERIALIZED_SIZE + sizeof(FwDpIdType)) * 2;

        // Initialize the data product container
        Fw::Success status = this->dpGet_SinusoidContainer(containerSize, this->m_container);
        if (status != Fw::Success::SUCCESS) {
            this->log_WARNING_HI_DpMemoryFailure(containerSize);
        } else {
            this->m_containerValid = true;
            this->m_container.setTimeTag(this->getTime());
            this->log_WARNING_HI_DpMemoryFailure_ThrottleClear();
        }
    }
    // If we have a valid container, serialize records into it
    if (this->m_containerValid) {
        Fw::Time currentFwTime = this->getTime();
        Fw::TimeValue currentTime = Fw::TimeValue(currentFwTime.getTimeBase(), currentFwTime.getContext(),
                                                  currentFwTime.getSeconds(), currentFwTime.getUSeconds());
        F64 time = static_cast<F64>(currentTime.get_seconds()) + static_cast<F64>(currentTime.get_useconds()) / 1.0e6;
        // Calculate sine and cosine records
        SinusoidRecordType sineRecord, cosineRecord;
        sineRecord.set_timeTag(currentTime);
        sineRecord.set_value(std::sin(time));
        cosineRecord.set_timeTag(currentTime);
        cosineRecord.set_value(std::cos(time));

        // Serialize the records into the data product container
        Fw::SerializeStatus status = this->m_container.serializeRecord_SineRecord(sineRecord);
        FW_ASSERT(status == Fw::SerializeStatus::FW_SERIALIZE_OK);
        status = this->m_container.serializeRecord_CosineRecord(cosineRecord);
        FW_ASSERT(status == Fw::SerializeStatus::FW_SERIALIZE_OK);
        this->m_count += 1;

        // If we've reached the record count, send the full product
        if (this->m_count == RECORD_COUNT) {
            this->dpSend(this->m_container);
            this->m_count = 0;
            this->m_containerValid = false;
        }
    }
}

}  // namespace DataProduct
