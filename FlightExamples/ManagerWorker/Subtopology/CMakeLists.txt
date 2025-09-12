
add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ManagerWorkerConfig")

register_fprime_module(
    EXCLUDE_FROM_ALL
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/ManagerWorker.fpp"
    HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/ManagerWorkerTopologyDefs.hpp"
    INTERFACE
    DEPENDS
        ManagerWorker_Subtopology_ManagerWorkerConfig
)
