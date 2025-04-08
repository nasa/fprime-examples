###########################
## Add OpenCV library    ##
###########################
# OpenCV needs to be installed on the system before running the build
# Follow https://docs.opencv.org/4.11.0/d0/d3d/tutorial_general_install.html

find_package(OpenCV REQUIRED)
message(STATUS "Found OpenCV: ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV version: ${OpenCV_VERSION}")
message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")

###########################
## Add ETL library       ##
###########################
# Make ETL available at the project level
# See https://fprime.jpl.nasa.gov/latest/docs/how-to/integrate-external-libraries 
# for more information on how to use FetchContent

# The below FetchContent directives would download the ETL library from GitHub and make it available
# at the project level. This is not needed since the ETL library is a submodule of the current project

# include(FetchContent)
# FetchContent_Declare(
#     etl
#     GIT_REPOSITORY https://github.com/ETLCPP/etl
#     GIT_TAG        20.40.0
# )
# FetchContent_MakeAvailable(etl)

# Since the ETL library is a submodule of the current project, we can add it directly
# with add_subdirectory and skip the FetchContent step above
add_subdirectory("${FPRIME_PROJECT_ROOT}/lib/etl" "${CMAKE_BINARY_DIR}/etl")


###########################
## Build OpenSSL library ##
###########################
include(ExternalProject)

set(OPENSSL_SOURCE_DIR ${FPRIME_PROJECT_ROOT}/lib/openssl)
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
  INSTALL_COMMAND make install_sw
  INSTALL_DIR ${OPENSSL_INSTALL_DIR}
)
# Since ExternalProject_Add will only build OpenSSL at project-build-time, we need to create the
# include directory so it exists at project-configure-time
file(MAKE_DIRECTORY ${OPENSSL_INCLUDE_DIR})
# Declare the properties needed for the OpenSSL::Crypto library
add_library(OpenSSL::Crypto STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_LOCATION ${OPENSSL_INSTALL_DIR}/lib/libcrypto.a)
set_property(TARGET OpenSSL::Crypto PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})
add_dependencies(OpenSSL::Crypto OpenSSL)

###########################
## Module subdirectories ##
###########################
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Types/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ImageProcessor/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Subtopology/")
