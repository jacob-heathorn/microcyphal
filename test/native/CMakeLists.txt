# Add a simple test both ways to verify both the pigweed and googletest frameworks
add_platform_test(gtest-ut-simple ut_simple.cpp)

# Manual tests
add_executable(hello-world hello_world.cpp)
platformify(hello-world)
target_link_libraries(hello-world microcyphal)

