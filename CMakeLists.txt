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

# Add Nunavut CMake module path and use official Nunavut functions
find_package(Nunavut REQUIRED PATHS "$ENV{NUNAVUT_ROOT}" NO_DEFAULT_PATH)

# Include our custom wrapper function
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_microcyphal_library.cmake)

# Generate Cyphal DSDL headers using our wrapper
add_microcyphal_library(
    NAME cyphal_generated_types
    NAMESPACE_PATH "$ENV{PUBLIC_REGULATED_DATA_TYPES_ROOT}/uavcan"
)

# Set the generated directory path for compatibility
set(CYPHAL_GENERATED_DIR "${cyphal_generated_types_GENERATED_DIR}" CACHE PATH "Directory containing generated Cyphal headers")
set(CYPHAL_LIB_TARGET ${cyphal_generated_types_LIB_TARGET})
set(CYPHAL_CODEGEN_TARGET ${cyphal_generated_types_CODEGEN_TARGET})

# Add the platform module here at the root of the tree.
include(platform)
include(subdirectories)
