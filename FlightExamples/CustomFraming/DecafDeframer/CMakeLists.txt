register_fprime_library(
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.cpp"
  AUTOCODER_INPUTS
    "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.fpp"
  DEPENDS
    Utils_Types
    CustomFraming_Types
)

### Unit Tests ###
register_fprime_ut(
  SOURCES
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafDeframerTestMain.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafDeframerTester.cpp"
  AUTOCODER_INPUTS
    "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.fpp"
  DEPENDS
    STest
  UT_AUTO_HELPERS
)
