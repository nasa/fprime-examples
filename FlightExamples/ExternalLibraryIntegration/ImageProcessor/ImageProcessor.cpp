// ======================================================================
// \title  ImageProcessor.cpp
// \author thomas-bc
// \brief  cpp file for ImageProcessor component implementation class
// ======================================================================

#include "ExternalLibraryIntegration/ImageProcessor/ImageProcessor.hpp"

namespace ExternalLibraryIntegration {

// ----------------------------------------------------------------------
// Component construction and destruction
// ----------------------------------------------------------------------

ImageProcessor ::ImageProcessor(const char* const compName) : ImageProcessorComponentBase(compName) {
    // Initialize the image vector with a fixed size (10 in this case)
    this->m_imageVector.resize(10);
}

ImageProcessor ::~ImageProcessor() {}

// ----------------------------------------------------------------------
// Component methods
// ----------------------------------------------------------------------

ExternalLibraryIntegration::ImageReadStatus ImageProcessor ::readImageAt_handler(FwIndexType portNum,
                                                              U8 index,
                                                              const Fw::StringBase& onboardPath) {
    ExternalLibraryIntegration::ImageReadStatus status = ExternalLibraryIntegration::ImageReadStatus::OTHER_ERROR;
    if (index < this->m_imageVector.size()) {
        // Read the image from the specified path and store it in the vector
        cv::Mat image = cv::imread(onboardPath.toChar(), cv::IMREAD_COLOR);
        if (!image.empty()) {
            this->m_imageVector[index] = image;
            // Log success
            this->log_ACTIVITY_HI_ImageReadSuccess(index);
            status = ExternalLibraryIntegration::ImageReadStatus::OK;
        } else {
            // Log failure
            this->log_ACTIVITY_HI_ImageReadFailure(index, ExternalLibraryIntegration::ImageReadStatus::OTHER_ERROR);
            status = ExternalLibraryIntegration::ImageReadStatus::OTHER_ERROR;
        }
    } else {
        // Log invalid index
        this->log_ACTIVITY_HI_ImageReadFailure(index, ExternalLibraryIntegration::ImageReadStatus::INVALID_INDEX);
        status = ExternalLibraryIntegration::ImageReadStatus::INVALID_INDEX;
    }
    return status;
}

// ----------------------------------------------------------------------
// Handler implementations for commands
// ----------------------------------------------------------------------

void ImageProcessor ::PROCESS_IMAGES_cmdHandler(FwOpcodeType opCode, U32 cmdSeq) {
    // PROCESS_IMAGES performs no actual processing in this example
    // but could be extended to process the images in m_imageVector.
    this->cmdResponse_out(opCode, cmdSeq, Fw::CmdResponse::OK);
}


}  // namespace ExternalLibraryIntegration
