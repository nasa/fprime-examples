####
# FPrime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
# UT_SOURCE_FILES: list of source files for unit tests
#
# More information in the F´ CMake API documentation:
# https://fprime.jpl.nasa.gov/latest/documentation/reference
#
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/OpenCvWrapper.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/OpenCvWrapper.cpp"
)

# OpenCV needs to be installed on the system before running the build
# Follow https://docs.opencv.org/4.11.0/d0/d3d/tutorial_general_install.html
find_package(OpenCV REQUIRED)


message("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA")
message("OpenCV_INCLUDE_DIRS: ${OpenCV_INCLUDE_DIRS}")
message("OpenCV_LIBS: ${OpenCV_LIBS}")

set(MOD_DEPS
  ${OpenCV_LIBS}
)

register_fprime_module()
target_include_directories(${FPRIME_CURRENT_MODULE} PUBLIC "${OpenCV_INCLUDE_DIRS}")

