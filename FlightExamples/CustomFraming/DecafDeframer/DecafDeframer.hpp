// ======================================================================
// \title  DecafDeframer.hpp
// \author thomas-bc
// \brief  hpp file for DecafDeframer component implementation class
// ======================================================================

#ifndef CustomFraming_DecafDeframer_HPP
#define CustomFraming_DecafDeframer_HPP

#include "CustomFraming/DecafDeframer/DecafDeframerComponentAc.hpp"
#include "Utils/Hash/Hash.hpp"

namespace CustomFraming {

class DecafDeframer final : public DecafDeframerComponentBase {


  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct DecafDeframer object
    DecafDeframer(const char* const compName  //!< The component name
    );

    //! Destroy DecafDeframer object
    ~DecafDeframer();

  private:
    // ----------------------------------------------------------------------
    // Handler implementations for user-defined typed input ports
    // ----------------------------------------------------------------------

    //! Handler implementation for frame
    //!
    //! Port to receive framed data. The handler will strip the header and trailer from the frame
    //! and pass the deframed data to the deframed output port.
    void dataIn_handler(FwIndexType portNum,  //!< The port number
                       Fw::Buffer& data,
                       const ComCfg::FrameContext& context) override;

    //! Handler implementation for dataReturnIn
    //!
    //! Port receiving back ownership of sent frame buffers
    void dataReturnIn_handler(FwIndexType portNum,  //!< The port number
                                Fw::Buffer& data,  //!< The buffer
                                const ComCfg::FrameContext& context) override;


};

}  // namespace CustomFraming

#endif
