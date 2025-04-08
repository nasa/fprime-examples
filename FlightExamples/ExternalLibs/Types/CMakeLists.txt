set(SOURCE_FILES
  "${CMAKE_CURRENT_LIST_DIR}/CryptoTypes.fpp"
  "${CMAKE_CURRENT_LIST_DIR}/OpenCvTypes.fpp"
)
set(MOD_DEPS
  Fw/Types
)
register_fprime_module()
