# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Manager/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Worker/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Subtopology/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExternalLibs/")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SubtopologyConfigs/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExamplesDeployment/")

