# CMake minimum version (run cmake --version to check)
CMAKE_MINIMUM_REQUIRED(VERSION 3.28)

# Ccache configuration for speedy builds
# This needs to be done before project to prevent a cmake infinite loop.
option(ENABLE_CCACHE "Enable ccache for faster builds" OFF)
if(ENABLE_CCACHE)
    find_program(CCACHE_FOUND ccache)
    if(CCACHE_FOUND)
        message(STATUS "Enabling ccache...")
        set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
        set(CMAKE_CXX_COMPILER "/usr/lib/ccache/bin/g++")  # CHANGEME - if your ccache installation path differs
    endif()
endif()

# Project details. Set project level language here
PROJECT(CHANGEME VERSION 1.0.0 LANGUAGES CXX)

# For clangd and clang tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set build output directories
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Debug info
message(STATUS "CMAKE_PROJECT_VERSION = ${CMAKE_PROJECT_VERSION}")
message(STATUS "Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler Version: ${CMAKE_CXX_COMPILER_VERSION}")

# Set compiler flags based on the compiler being used
if(MSVC)
    add_compile_options("/W4" "$<$<CONFIG:RELEASE>:/O2>")
else()
    add_compile_options("-Wall" "-Wextra" "-Werror" "$<$<CONFIG:RELEASE>:-O3>" "$<$<CONFIG:DEBUG>:-g>" "-std=c++23")  # Note C++23 requires g++-14
    if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        add_compile_options("-stdlib=libc++")
    else()
        add_compile_options("-Wno-builtin-macro-redefined")
    endif()
endif()

# Enable and enforce C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Boost pre-requisites
set(BOOST_COMPONENTS system iostreams) 
find_package( Boost REQUIRED COMPONENTS ${BOOST_COMPONENTS} )

# This plugin is used to fetch and build required libraries from source (e.g. gtest)
include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

add_subdirectory(proto)
add_subdirectory(lib)
add_subdirectory(mainProject)
add_subdirectory(test)

# Documentation with doxygen
find_package(Doxygen)
option(BUILD_DOCUMENTATION "Build documentation (requires Doxygen)" ${DOXYGEN_FOUND})
if(BUILD_DOCUMENTATION AND CMAKE_BUILD_TYPE MATCHES RELEASE)
    if(NOT DOXYGEN_FOUND)
         message(FATAL_ERROR "Cannot find Doxygen package to build documentation.")
    endif()

    set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile)  # CHANGEME - set input doxyfile path. This will look in project root by default
    set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)

    configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

    message(STATUS "Doxygen build started.")

    add_custom_target(
        docs ALL
        COMMAND
            $<$<CONFIG:Release>:${DOXYGEN_EXECUTABLE} ${DOXYFILE_IN}>
            $<$<NOT:$<CONFIG:Release>>:${CMAKE_COMMAND} -E echo "Only done in Release builds" >
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )
endif()
