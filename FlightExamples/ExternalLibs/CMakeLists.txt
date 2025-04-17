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
set(OPENSSL_LIBCRYPTO_LIB ${OPENSSL_INSTALL_DIR}/lib/libcrypto.a)

ExternalProject_Add(
    OpenSSL
    SOURCE_DIR ${OPENSSL_SOURCE_DIR}
    CONFIGURE_COMMAND
        ${OPENSSL_SOURCE_DIR}/config
        --prefix=${OPENSSL_INSTALL_DIR}
        --openssldir=${OPENSSL_INSTALL_DIR}
        --libdir=lib # this makes sure libcrypto.a is in lib/ (e.g. instead of lib64 on some systems)
        no-tests
    BUILD_COMMAND make -j8 build_generated libcrypto.a
    TEST_COMMAND ""
    INSTALL_COMMAND make install_sw
    INSTALL_DIR ${OPENSSL_INSTALL_DIR}
    BUILD_BYPRODUCTS ${OPENSSL_INCLUDE_DIR} ${OPENSSL_LIBCRYPTO_LIB} # allows the build to know libcrypto.a is a byproduct of this ExternalProject_Add
)
# Since ExternalProject_Add will only build OpenSSL at project-build-time, we need to create the
# include directory so it exists at project-configure-time
file(MAKE_DIRECTORY ${OPENSSL_INCLUDE_DIR})
# Declare the properties needed for the OpenSSL::Crypto library
add_library(OpenSSL::Crypto STATIC IMPORTED GLOBAL)
set_property(TARGET OpenSSL::Crypto PROPERTY IMPORTED_LOCATION ${OPENSSL_LIBCRYPTO_LIB})
set_property(TARGET OpenSSL::Crypto PROPERTY INTERFACE_INCLUDE_DIRECTORIES ${OPENSSL_INCLUDE_DIR})
add_dependencies(OpenSSL::Crypto OpenSSL)

###########################
## Module subdirectories ##
###########################
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Types/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/Subtopology/")
if (FPRIME_EXAMPLES_USE_OPENCV)
    add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ImageProcessor/")
else()
    message(STATUS "[OpenCV] OpenCV disabled: Skipping ImageProcessor module.")
endif()
