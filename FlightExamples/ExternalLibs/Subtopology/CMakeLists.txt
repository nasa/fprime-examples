set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/intentionally-empty.cpp"
)

if (FPRIME_EXAMPLES_USE_OPENCV)
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology-withOpenCV.fpp")
else()
    list(APPEND SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology-noOpenCV.fpp")
endif ()

register_fprime_module()

set_target_properties(
    ${FPRIME_CURRENT_MODULE}
    PROPERTIES
    SOURCES "${CMAKE_CURRENT_LIST_DIR}/intentionally-empty.cpp"
)
