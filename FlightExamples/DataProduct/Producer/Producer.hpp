// ======================================================================
// \title  Producer.hpp
// \author mstarch
// \brief  hpp file for Producer component implementation class
// ======================================================================

#ifndef DataProduct_Producer_HPP
#define DataProduct_Producer_HPP

#include "DataProduct/Producer/ProducerComponentAc.hpp"

namespace DataProduct {

class Producer final : public ProducerComponentBase {
  public:
    constexpr static const FwSizeType RECORD_COUNT = 100;  //!< Number of records of each type in the data product
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Producer object
    Producer(const char* const compName  //!< The component name
    );

    //! Destroy Producer object
    ~Producer();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Schedule input port
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;

  private:
    FwSizeType m_count;       //!< Count of serialized records
    DpContainer m_container;  //!< Data product container (currently allocated)
    bool m_containerValid;    //!< Whether the container is valid
};

}  // namespace DataProduct

#endif
