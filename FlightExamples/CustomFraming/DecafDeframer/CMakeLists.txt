####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.cpp"
)

set(MOD_DEPS
    Utils_Types
    CustomFraming_Types
)

register_fprime_module()


#### UTs ####
set(UT_SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/DecafDeframer.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafDeframerTester.cpp"
  "${CMAKE_CURRENT_LIST_DIR}/test/ut/DecafDeframerTestMain.cpp"
)
set(UT_MOD_DEPS
    STest
)
set(UT_AUTO_HELPERS ON)

register_fprime_ut()
