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
  "${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper.cpp"
)

set(MOD_DEPS
  # OpenSSL dependency
  OpenSSL::Crypto
  # additional dependencies
  ExternalLibs/Types
  Fw/Logger
  etl::etl
)

register_fprime_module()


set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/OpenSslWrapperTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/OpenSslWrapperTestMain.cpp"
)
set(UT_AUTO_HELPERS ON)
register_fprime_ut()
