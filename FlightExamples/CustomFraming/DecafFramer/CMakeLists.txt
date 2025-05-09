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
  "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.cpp"
)

set(MOD_DEPS
  CustomFraming_Types
)

register_fprime_module()


### Unit Tests ###
set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DecafFramer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafFramerTestMain.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafFramerTester.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
