// ======================================================================
// \title  ImageProcessorTester.cpp
// \author thomas-bc
// \brief  cpp file for ImageProcessor component test harness implementation class
// ======================================================================

#include "ImageProcessorTester.hpp"

namespace ExternalLibs {

// ----------------------------------------------------------------------
// Construction and destruction
// ----------------------------------------------------------------------

ImageProcessorTester ::ImageProcessorTester()
    : ImageProcessorGTestBase("ImageProcessorTester", ImageProcessorTester::MAX_HISTORY_SIZE), component("ImageProcessor") {
    this->initComponents();
    this->connectPorts();
}

ImageProcessorTester ::~ImageProcessorTester() {}

// ----------------------------------------------------------------------
// Tests
// ----------------------------------------------------------------------

void ImageProcessorTester ::testReadImage() {
    // no-op
    this->clearEvents();
}

}  // namespace ExternalLibs
