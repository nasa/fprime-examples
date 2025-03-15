# Make ETL available at the project level
# See <include link to pattern> for more information on how to use FetchContent
include(FetchContent)
FetchContent_Declare(
    etl
    GIT_REPOSITORY https://github.com/ETLCPP/etl
    GIT_TAG        20.40.0
)
FetchContent_MakeAvailable(etl)


# This CMake file is intended to register project-wide objects.
# This allows for reuse between deployments, or other projects.
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Manager/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Worker/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorker/Subtopology/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExternalLibraryIntegration/")

add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/SubtopologyConfigs/")
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExamplesDeployment/")

