// ======================================================================
// \title  DecafFramer.hpp
// \author thomas-bc
// \brief  hpp file for DecafFramer component implementation class
// ======================================================================

#ifndef CustomFraming_DecafFramer_HPP
#define CustomFraming_DecafFramer_HPP

#include "CustomFraming/DecafFramer/DecafFramerComponentAc.hpp"

namespace CustomFraming {

class DecafFramer final : public DecafFramerComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct DecafFramer object
    DecafFramer(const char* const compName  //!< The component name
    );

    //! Destroy DecafFramer object
    ~DecafFramer();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for comStatusIn
    //!
    //! Port receiving the general status from the downstream component
    //! indicating it is ready or not-ready for more input
    void comStatusIn_handler(FwIndexType portNum,    //!< The port number
                             Fw::Success& condition  //!< Condition success/failure
                             ) override;

    //! Handler implementation for dataIn
    //!
    //! Port to receive data to frame, in a Fw::Buffer with optional context
    void dataIn_handler(FwIndexType portNum,  //!< The port number
                        Fw::Buffer& data,
                        const ComCfg::FrameContext& context) override;

    //! Handler implementation for dataReturnIn
    //!
    //! Buffer coming from a deallocate call in a ComDriver component
    void dataReturnIn_handler(FwIndexType portNum,  //!< The port number
                                Fw::Buffer& data,
                                const ComCfg::FrameContext& context) override;

    // ----------------------------------------------------------------------
    // Helpers
    // ----------------------------------------------------------------------

    //! Helper function to send the framed data out of the component
    //! This sequentially calls both frameDataOut and frameStreamOut ports if connected
    void framedOut_helper(Fw::Buffer& frameBuffer,
                          const ComCfg::FrameContext& context);
};

}  // namespace CustomFraming

#endif
