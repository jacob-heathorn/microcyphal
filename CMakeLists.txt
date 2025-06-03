cmake_minimum_required(VERSION 3.27.4)

project(microcyphal VERSION 1.0 LANGUAGES C CXX ASM)

# Use C++17. Force it, No Extensions (-std=c++17 not -std=gnu++17) to increase portability.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable testing with ctest
enable_testing()

# Make the platform module accessible from anywhere in the tree.
list(APPEND CMAKE_MODULE_PATH ${PLATFORM_PATH})

# Include our custom wrapper function (which also finds Nunavut)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_microcyphal_library.cmake)

# Generate Cyphal DSDL headers using our wrapper
add_microcyphal_library(
    NAME standard_uavcan_types
    NAMESPACE_PATH "$ENV{PUBLIC_REGULATED_DATA_TYPES_ROOT}/uavcan"
)

# Add the platform module here at the root of the tree.
include(platform)
include(subdirectories)
