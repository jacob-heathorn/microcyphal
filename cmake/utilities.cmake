# Include guard
if(DEFINED _ADD_MICROCYPHAL_LIBRARY_CMAKE_)
    return()
endif()
set(_ADD_MICROCYPHAL_LIBRARY_CMAKE_ TRUE)

# Find Nunavut package in the specified path
find_package(Nunavut REQUIRED PATHS "$ENV{NUNAVUT_ROOT}" NO_DEFAULT_PATH)

# Custom wrapper function for add_cyphal_library
function(add_microcyphal_library)
    cmake_parse_arguments(
        ARG
        ""  # Options
        "NAME;NAMESPACE_PATH"  # One-value arguments
        ""  # Multi-value arguments
        ${ARGN}
    )

    # Validate required arguments
    if(NOT ARG_NAME)
        message(FATAL_ERROR "add_microcyphal_library: NAME is required")
    endif()
    if(NOT ARG_NAMESPACE_PATH)
        message(FATAL_ERROR "add_microcyphal_library: NAMESPACE_PATH is required")
    endif()

    # Find all DSDL files in the namespace
    file(GLOB_RECURSE DSDL_FILES "${ARG_NAMESPACE_PATH}/*.dsdl")
    
    # Call the underlying add_cyphal_library function
    add_cyphal_library(
        NAME ${ARG_NAME}
        EXACT_NAME
        LANGUAGE cpp
        LANGUAGE_STANDARD c++${CMAKE_CXX_STANDARD}
        ALLOW_EXPERIMENTAL_LANGUAGES
        PYDSDL_PATH "$ENV{PYDSDL_ROOT}"
        DSDL_NAMESPACES "${ARG_NAMESPACE_PATH}"
        DSDL_FILES ${DSDL_FILES}
        EXTRA_GENERATOR_ARGS "--allow-unregulated-fixed-port-id"
        OUTPUT_DIR "${CMAKE_CURRENT_BINARY_DIR}/.bin/generated/cpp${CMAKE_CXX_STANDARD}"
        OUT_LIBRARY_TARGET ${ARG_NAME}_LIB_TARGET
        OUT_CODEGEN_TARGET ${ARG_NAME}_CODEGEN_TARGET
    )

    # Export the generated directory path
    set(${ARG_NAME}_GENERATED_DIR "${CMAKE_CURRENT_BINARY_DIR}/.bin/generated/cpp${CMAKE_CXX_STANDARD}" PARENT_SCOPE)
    
    # Also export the library and codegen targets
    set(${ARG_NAME}_LIB_TARGET ${${ARG_NAME}_LIB_TARGET} PARENT_SCOPE)
    set(${ARG_NAME}_CODEGEN_TARGET ${${ARG_NAME}_CODEGEN_TARGET} PARENT_SCOPE)
endfunction()