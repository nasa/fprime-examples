// ======================================================================
// \title  ImageProcessor.hpp
// \author thomas-bc
// \brief  hpp file for ImageProcessor component implementation class
// ======================================================================

#ifndef ExternalLibs_ImageProcessor_HPP
#define ExternalLibs_ImageProcessor_HPP

#include "ExternalLibs/ImageProcessor/ImageProcessorComponentAc.hpp"

// ETL Library
#include "etl/vector.h"
// OpenCV Library
#include <opencv2/opencv.hpp>

namespace ExternalLibs {

class ImageProcessor : public ImageProcessorComponentBase {
  public:
    // ----------------------------------------------------------------------
    // Component construction and destruction
    // ----------------------------------------------------------------------

    //! Construct ImageProcessor object
    ImageProcessor(const char* const compName  //!< The component name
    );

    //! Destroy ImageProcessor object
    ~ImageProcessor();

  PRIVATE:
    //! Handler implementation for readImageAt
    ExternalLibs::ImageReadStatus readImageAt_handler(FwIndexType portNum,               //!< The port number
      U8 index,                          //!< Index to insert the image at in the
      const Fw::StringBase& onboardPath  //!< Path to onboard image to read
      ) override;

    //! Handler implementation for command PROCESS_IMAGES
    //!
    //! Process images loaded into the internal array
    void PROCESS_IMAGES_cmdHandler(FwOpcodeType opCode,  //!< The opcode
      U32 cmdSeq            //!< The command sequence number
      ) override;

  PRIVATE:
    etl::vector<cv::Mat, 10> m_imageVector;  //!< Vector to hold OpenCV images to be processed

};

}  // namespace ExternalLibs

#endif
