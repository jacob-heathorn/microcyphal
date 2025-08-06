target_link_libraries(microcyphal INTERFACE ftl-native)

# Add a simple test both ways to verify both the pigweed and googletest frameworks
add_platform_test(ut-simple ut_simple.cpp)
add_platform_test(ut-cyphal
  ut_udp_frame.cpp
  ut_serialization.cpp
  ut_publisher.cpp
  ut_subscriber.cpp
)
target_link_libraries(ut-cyphal microcyphal)

# Manual tests
add_executable(hello-publisher hello_publisher.cpp)
platformify(hello-publisher)
target_link_libraries(hello-publisher microcyphal)

add_executable(hello-subscriber hello_subscriber.cpp)
platformify(hello-subscriber)
target_link_libraries(hello-subscriber microcyphal)

add_executable(debug-subscriber debug_subscriber.cpp)
platformify(debug-subscriber)
target_link_libraries(debug-subscriber microcyphal)
