set(SUBTOPOLOGY_FILE)
if (FPRIME_EXAMPLES_USE_OPENCV)
    set(SUBTOPOLOGY_FILE "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology.fpp")
else()
    set(SUBTOPOLOGY_FILE "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology-empty.fpp")
endif ()


add_fprime_subdirectory("${CMAKE_CURRENT_LIST_DIR}/ExternalLibsConfig")

register_fprime_module(
    EXCLUDE_FROM_ALL
    AUTOCODER_INPUTS
        "${SUBTOPOLOGY_FILE}"
    HEADERS
        "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsTopologyDefs.hpp"
    INTERFACE
    DEPENDS
        ExternalLibs_Subtopology_ExternalLibsConfig
)
