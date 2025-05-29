include_guard(GLOBAL)

# Build forge native subdirectories.
add_subdirectory(
  $ENV{FORGE_ROOT}/firmware/ftl
  ${CMAKE_BINARY_DIR}/forge/firmware/ftl
)
add_subdirectory(
  $ENV{FORGE_ROOT}/firmware/native
  ${CMAKE_BINARY_DIR}/forge/firmware/native
)

# Microcyphal
add_subdirectory(
  $ENV{MICROCYPHAL_ROOT}/test/native
  ${CMAKE_BINARY_DIR}/microcyphal/test/native
)
