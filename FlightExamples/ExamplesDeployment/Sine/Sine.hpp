// ======================================================================
// \title  Sine.hpp
// \author mstarch
// \brief  hpp file for Sine component implementation class
// ======================================================================

#ifndef ExamplesDeployment_Sine_HPP
#define ExamplesDeployment_Sine_HPP

#include "ExamplesDeployment/Sine/SineComponentAc.hpp"

namespace ExamplesDeployment {

class Sine final : public SineComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct Sine object
    Sine(const char* const compName  //!< The component name
    );

    //! Destroy Sine object
    ~Sine();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for run
    //!
    //! Rate group input port
    void run_handler(FwIndexType portNum,  //!< The port number
                     U32 context           //!< The call order
                     ) override;
};

}  // namespace ExamplesDeployment

#endif
