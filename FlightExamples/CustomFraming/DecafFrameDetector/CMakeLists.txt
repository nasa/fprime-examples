####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####

register_fprime_library(
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/DecafFrameDetector.cpp"
  DEPENDS
    Utils_Types
    CustomFraming_Types
)
