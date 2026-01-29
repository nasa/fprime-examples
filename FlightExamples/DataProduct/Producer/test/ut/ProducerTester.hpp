// ======================================================================
// \title  ProducerTester.hpp
// \author mstarch
// \brief  hpp file for Producer component test harness implementation class
// ======================================================================

#ifndef DataProduct_ProducerTester_HPP
#define DataProduct_ProducerTester_HPP

#include "DataProduct/Producer/Producer.hpp"
#include "DataProduct/Producer/ProducerGTestBase.hpp"

namespace DataProduct {

class ProducerTester final : public ProducerGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 210;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object ProducerTester
    ProducerTester();

    //! Destroy object ProducerTester
    ~ProducerTester();

    Fw::Success::T productGet_handler(FwDpIdType id, FwSizeType dataSize, Fw::Buffer& buffer) override;

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! Test data product generation
    void test_data_product_generation();

    //! Test data product allocation failure handling
    void test_data_failed_allocate();

  private:
    // ----------------------------------------------------------------------
    // Helper functions
    // ----------------------------------------------------------------------

    //! Connect ports
    void connectPorts();

    //! Initialize components
    void initComponents();

  private:
    // ----------------------------------------------------------------------
    // Member variables
    // ----------------------------------------------------------------------

    //! The component under test
    Producer component;
    //! Size of buffer for productGet handler
    constexpr static FwSizeType BUFFER_SIZE =
        Fw::DpContainer::MIN_PACKET_SIZE +
        (2 * (SinusoidRecordType::SERIALIZED_SIZE + sizeof(FwDpIdType)) * Producer::RECORD_COUNT);
    //! Buffer for productGet handler
    U8 m_buffer[BUFFER_SIZE];

    bool m_allocation_failure = false;  //!< Whether to simulate allocation failure
};

}  // namespace DataProduct

#endif
