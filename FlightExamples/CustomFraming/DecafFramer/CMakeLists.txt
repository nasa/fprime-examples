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

register_fprime_library(
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.cpp"
  AUTOCODER_INPUTS
    "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.fpp"
  DEPENDS
    CustomFraming_Types
)


### Unit Tests ###
set(UT_AUTO_HELPERS ON)
register_fprime_ut(
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafFramerTestMain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafFramerTester.cpp"
  AUTOCODER_INPUTS
    "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.fpp"
)
