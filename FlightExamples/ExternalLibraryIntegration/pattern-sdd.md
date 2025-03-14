# How-To: Integrate an external Library

> [!TIP]
> For this How-To guide and many other advanced F´ CMake use cases, it is recommended to have a basic understanding of CMake. If you are unfamiliar with CMake, please refer to the [CMake documentation](https://cmake.org/getting-started/). They provide a [great tutorial to get you started](https://cmake.org/cmake/help/latest/guide/tutorial/index.html).

It is common practice to use third-party libraries in F´ projects. CMake provides multiple ways to integrate external libraries into a project, and the F´ build system facilitates it even further. This document will cover the different ways to integrate external libraries into your F´ project.

Each section below is a different method; they are listed by order of complexity.

> [!NOTE]
> The source code for the examples shown in this guide can be found in our examples repo here: [https://github.com/nasa/fprime-examples/tree/devel/FlightExamples/ExternalLibraryIntegration](https://github.com/nasa/fprime-examples/tree/devel/FlightExamples/ExternalLibraryIntegration)


## Pre-compiled Libraries

A pre-compiled library is a library that has already been compiled and is ready to be used, often named `lib<libName>.a` or `lib<libName>.so`. There are many ways to obtain pre-compiled libraries, such as downloading them from a package manager or building them from source yourself.

To integrate a pre-compiled library, you need to add the path of that library to `MOD_DEPS` of the module(s) that depend on it (MOD_DEPS: module dependencies). The following example demonstrates how to integrate a the OpenSSL `libcrypto` library into an F´ wrapper component:

```cmake
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/OpenSslWrapper.cpp"
)
set(OPENSSL_CRYPTO_LIB_PATH "${FPRIME_PROJECT_ROOT}/lib/libssl/libcrypto.a")
set(MOD_DEPS
  ${OPENSSL_CRYPTO_LIB_PATH}
)

register_fprime_module()
```

The necessary headers to be included should be added under the libraries include directory, under `<FPRIME_PROJECT_ROOT>/lib/include`. This path is automatically added to the include directories by F´ at the project level.

An example of the OpenSslWrapper component using this pre-compiled approach is shown here: [https://github.com/nasa/fprime-examples/tree/devel/FlightExamples/ExternalLibraryIntegration/OpenSslWrapper](https://github.com/nasa/fprime-examples/tree/devel/FlightExamples/ExternalLibraryIntegration/OpenSslWrapper)

## Source Code Libraries

If you have the source code for a library, multiple methods can be used to integrate it into your project. 

### Existing CMake Project: FetchContent

Many popular libraries are available as CMake projects, and the easiest way to integrate them is to use the `FetchContent` module. This module allows you to download and build the library as part of your project.
The following code demonstrates how to integrate the popular OpenCV library using `FetchContent`:

```cmake
include(FetchContent)
FetchContent_Declare(
  OpenCV
  GIT_REPOSITORY https://github.com/opencv/opencv.git
  GIT_TAG 4.5.1
)
FetchContent_MakeAvailable(OpenCV)
```

Then, in a component's CMakeLists.txt file, you can link against the OpenCV library like this:

```cmake
set(MOD_DEPS
  OpenCV
)
```




### ExternalProject_Add



- ExternalProject_Add is running configure/build at project build-time so we need to make sure `openssl_lib` is a dependency of the current module so parallel builds don't break
- Very complete API on CMake side, see: https://cmake.org/cmake/help/v3.31/module/ExternalProject.html#explicit-step-management
