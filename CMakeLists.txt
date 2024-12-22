################################################################################
# Copyright (c) 2021-2024 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#       202?.??.?? Initial version
#       2024.12.21 Removed `portable_target` dependency.
################################################################################
cmake_minimum_required (VERSION 3.19)
project(griotte-ALL CXX C)

cmake_policy(SET CMP0077 NEW)

option(GRIOTTE__BUILD_STRICT "Build with strict policies: C++ standard required, C++ extension is OFF etc" ON)
option(GRIOTTE__BUILD_TESTS "Build tests" OFF)
option(GRIOTTE__BUILD_DEMO "Build demo" OFF)

option(GRIOTTE__BUILD_SHARED "Enable build shared library" OFF)
option(GRIOTTE__SFML_BACKEND "Enable SFML backend" ON)

set(GRIOTTE__OUTPUT_DIR "${CMAKE_BINARY_DIR}/output")
get_property(_runtime_output_directory GLOBAL PROPERTY RUNTIME_OUTPUT_DIRECTORY)
get_property(_library_output_directory GLOBAL PROPERTY LIBRARY_OUTPUT_DIRECTORY)
get_property(_archive_output_directory GLOBAL PROPERTY ARCHIVE_OUTPUT_DIRECTORY)

if (NOT _runtime_output_directory)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${GRIOTTE__OUTPUT_DIR})
endif()

if (NOT _library_output_directory)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${GRIOTTE__OUTPUT_DIR})
endif()

if (NOT _archive_output_directory)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${GRIOTTE__OUTPUT_DIR})
endif()

if (GRIOTTE__BUILD_STRICT)
    if (NOT CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 17)
    endif()

    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++XX rather than -std=gnu++XX
endif()

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/output)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})

set(FETCHCONTENT_UPDATES_DISCONNECTED_CMRC ON)

message(STATUS "Fetching cmrc ...")
include(FetchContent)
FetchContent_Declare(cmrc
    GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
    GIT_TAG master
    GIT_PROGRESS TRUE
    GIT_SHALLOW 1
    SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/cmrc
    SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/cmrc)
FetchContent_MakeAvailable(cmrc)
message(STATUS "Fetching cmrc complete")

include(${CMAKE_CURRENT_LIST_DIR}/library.cmake)

if (GRIOTTE__BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (GRIOTTE__BUILD_DEMO)
    add_subdirectory(demo)
endif()

include(GNUInstallDirs)

install(TARGETS griotte
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
