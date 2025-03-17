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

# OpenCV needs to be installed on the system before running the build
# Follow https://docs.opencv.org/4.11.0/d0/d3d/tutorial_general_install.html
find_package(OpenCV REQUIRED)
message(STATUS "Found OpenCV_LIBS: ${OpenCV_LIBS}")

set(MOD_DEPS
  opencv_core
  opencv_imgcodecs
  opencv_imgproc
  etl::etl
)
register_fprime_module()


set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ImageProcessor.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/ImageProcessorTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/ImageProcessorTestMain.cpp"
)
set(UT_MOD_DEPS
  # UT_MOD_DEPS does not need to include the library dependencies as they are
  # already included in the module under test
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
