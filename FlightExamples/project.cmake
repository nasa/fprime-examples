# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/DataProducts/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExternalLibs/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/CustomFraming/")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExamplesDeployment/")

