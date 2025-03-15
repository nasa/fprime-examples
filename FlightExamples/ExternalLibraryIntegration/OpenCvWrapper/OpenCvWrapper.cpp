// ======================================================================
// \title  OpenCvWrapper.cpp
// \author chammard
// \brief  cpp file for OpenCvWrapper component implementation class
// ======================================================================

#include "ExternalLibraryIntegration/OpenCvWrapper/OpenCvWrapper.hpp"

// OpenCV library
#include <opencv2/opencv.hpp>

// ETL library
#include "etl/vector.h"


namespace ExternalLibraryIntegration {
  
  // ----------------------------------------------------------------------
  // Component construction and destruction
  // ----------------------------------------------------------------------

  OpenCvWrapper ::
    OpenCvWrapper(const char* const compName) :
      OpenCvWrapperComponentBase(compName)
  {
    cv::Mat image;
    etl::vector<int, 10> v1(10);

    for (int i = 0; i < 10; ++i) {
      printf("v1[%d] = %d\n", i, v1[i]);
    }
    printf("AAAAAAAAAABBBB OpenCV ETL That worked!!!\n");
  }

  OpenCvWrapper ::
    ~OpenCvWrapper()
  {

  }

}
