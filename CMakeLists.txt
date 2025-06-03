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

# Generate Cyphal DSDL headers using official Nunavut CMake functions
file(GLOB_RECURSE DSDL_FILES "$ENV{PUBLIC_REGULATED_DATA_TYPES_ROOT}/uavcan/*.dsdl")

add_cyphal_library(
    NAME cyphal_generated_types
    EXACT_NAME
    LANGUAGE cpp
    LANGUAGE_STANDARD c++${CMAKE_CXX_STANDARD}
    ALLOW_EXPERIMENTAL_LANGUAGES
    PYDSDL_PATH "$ENV{PYDSDL_ROOT}"
    DSDL_NAMESPACES "$ENV{PUBLIC_REGULATED_DATA_TYPES_ROOT}/uavcan"
    DSDL_FILES ${DSDL_FILES}
    EXTRA_GENERATOR_ARGS "--allow-unregulated-fixed-port-id"
    OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/.bin/generated/cpp${CMAKE_CXX_STANDARD}"
    OUT_LIBRARY_TARGET CYPHAL_LIB_TARGET
    OUT_CODEGEN_TARGET CYPHAL_CODEGEN_TARGET
)

set(CYPHAL_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.bin/generated/cpp${CMAKE_CXX_STANDARD}" CACHE PATH "Directory containing generated Cyphal headers")

# Add the platform module here at the root of the tree.
include(platform)
include(subdirectories)
