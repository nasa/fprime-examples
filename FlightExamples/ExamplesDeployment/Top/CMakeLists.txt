####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding files
# MOD_DEPS: (optional) module dependencies
####

set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/instances.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/topology.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/ExamplesDeploymentTopology.cpp"
)
set(MOD_DEPS
  Fw/Logger
  # Communication Implementations
  Drv/Udp
  Drv/TcpClient
  CustomFraming_DecafFrameDetector
)

register_fprime_module()
