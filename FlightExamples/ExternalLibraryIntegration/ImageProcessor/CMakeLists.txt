####
# FPrime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/docs/reference
#
####

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
  ExternalLibraryIntegration/Types
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
