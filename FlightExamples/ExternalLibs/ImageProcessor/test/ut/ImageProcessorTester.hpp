// ======================================================================
// \title  ImageProcessorTester.hpp
// \author thomas-bc
// \brief  hpp file for ImageProcessor component test harness implementation class
// ======================================================================

#ifndef ExternalLibs_ImageProcessorTester_HPP
#define ExternalLibs_ImageProcessorTester_HPP

#include "ExternalLibs/ImageProcessor/ImageProcessor.hpp"
#include "ExternalLibs/ImageProcessor/ImageProcessorGTestBase.hpp"

namespace ExternalLibs {

class ImageProcessorTester final : public ImageProcessorGTestBase {
  public:
    // ----------------------------------------------------------------------
    // Constants
    // ----------------------------------------------------------------------

    // Maximum size of histories storing events, telemetry, and port outputs
    static const FwSizeType MAX_HISTORY_SIZE = 10;

    // Instance ID supplied to the component instance under test
    static const FwEnumStoreType TEST_INSTANCE_ID = 0;

  public:
    // ----------------------------------------------------------------------
    // Construction and destruction
    // ----------------------------------------------------------------------

    //! Construct object ImageProcessorTester
    ImageProcessorTester();

    //! Destroy object ImageProcessorTester
    ~ImageProcessorTester();

  public:
    // ----------------------------------------------------------------------
    // Tests
    // ----------------------------------------------------------------------

    //! To do
    void testReadImage();

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
    ImageProcessor component;
};

}  // namespace ExternalLibs

#endif
