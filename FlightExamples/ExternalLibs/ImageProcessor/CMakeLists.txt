###########################
## Add OpenCV library    ##
###########################
# OpenCV needs to be installed on the system before running the build
# Follow https://docs.opencv.org/4.11.0/d0/d3d/tutorial_general_install.html

find_package(OpenCV REQUIRED GLOBAL) # note: need GLOBAL for F Prime introspection (is IMOPRTED library in find_package)
message(STATUS "[OpenCV] Found OpenCV version ${OpenCV_VERSION} at ${OpenCV_INCLUDE_DIRS}")
message(STATUS "[OpenCV] OpenCV libraries: ${OpenCV_LIBS}")


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
