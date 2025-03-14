// ======================================================================
// \title  OpenCvWrapper.cpp
// \author chammard
// \brief  cpp file for OpenCvWrapper component implementation class
// ======================================================================

#include "ExternalLibraryIntegration/OpenCvWrapper/OpenCvWrapper.hpp"
#include <opencv2/opencv.hpp>

namespace ExternalLibraryIntegration {
  
  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  OpenCvWrapper ::
    OpenCvWrapper(const char* const compName) :
      OpenCvWrapperComponentBase(compName)
  {
    cv::Mat image;
    printf("AAAAAAAAAABBBB OpenCV That worked!!!\n");
  }

  OpenCvWrapper ::
    ~OpenCvWrapper()
  {

  }

}
