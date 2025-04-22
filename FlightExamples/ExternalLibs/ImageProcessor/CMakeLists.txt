###########################
## Add OpenCV library    ##
###########################
# OpenCV needs to be installed on the system before running the build
# Follow https://docs.opencv.org/4.11.0/d0/d3d/tutorial_general_install.html

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.cpp"
)

set(MOD_DEPS
  # OpenCV dependencies
  opencv_core
  opencv_imgcodecs
  opencv_imgproc
  # ETL
  etl::etl
  # F´ types
  ExternalLibs/Types
)
register_fprime_module()


set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/ImageProcessorTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/ImageProcessorTestMain.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
