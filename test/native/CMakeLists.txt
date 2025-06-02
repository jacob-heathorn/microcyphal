# Add a simple test both ways to verify both the pigweed and googletest frameworks
add_platform_test(ut-simple ut_simple.cpp)
add_platform_test(ut-cyphal
  ut_udp_frame.cpp
  ut_serialization.cpp
)
target_link_libraries(ut-cyphal microcyphal)

# Manual tests
add_executable(hello-world hello_world.cpp)
platformify(hello-world)
target_link_libraries(hello-world microcyphal)
