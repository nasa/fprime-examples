# set(SOURCE_FILES)
# if (FPRIME_EXAMPLES_USE_OPENCV)
#     set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology-withOpenCV.fpp")
# else()
#     set(SOURCE_FILES "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsSubtopology-noOpenCV.fpp")
# endif ()


register_fprime_config(
    EXCLUDE_FROM_ALL
    AUTOCODER_INPUTS
        "${CMAKE_CURRENT_LIST_DIR}/ExternalLibsConfig.fpp"
    INTERFACE
)
