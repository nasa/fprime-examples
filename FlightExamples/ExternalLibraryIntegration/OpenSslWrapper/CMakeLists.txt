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

include(ExternalProject)

set(OPENSSL_SOURCE_DIR ${FPRIME_PROJECT_ROOT}/lib/openssl) # default path by CMake
set(OPENSSL_INSTALL_DIR ${CMAKE_BINARY_DIR}/openssl)
set(OPENSSL_INCLUDE_DIR ${OPENSSL_INSTALL_DIR}/include)

ExternalProject_Add(
  OpenSSL
  SOURCE_DIR ${OPENSSL_SOURCE_DIR}
  CONFIGURE_COMMAND
    ${OPENSSL_SOURCE_DIR}/config
    --prefix=${OPENSSL_INSTALL_DIR}
    --openssldir=${OPENSSL_INSTALL_DIR}
  BUILD_COMMAND make
  TEST_COMMAND ""
  INSTALL_COMMAND make install
  INSTALL_DIR ${OPENSSL_INSTALL_DIR}
)

set(MOD_DEPS
  OpenSSL # dependency on the above-defined OpenSSL library - without this line openssl_lib will not be built
  ${OPENSSL_INSTALL_DIR}/lib/libcrypto.a # dependency on the actual library file needed for linking
  etl::etl
  )

register_fprime_module()
target_include_directories(${FPRIME_CURRENT_MODULE} PUBLIC "${OPENSSL_INCLUDE_DIR}")

