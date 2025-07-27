################################################################################
# Copyright (c) 2021-2025 Vladislav Trifochkin
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
option(GRIOTTE__DISABLE_FETCH_CONTENT "Disable fetch content if sources of dependencies already exists in the working tree (checks .git subdirectory)" ON)

if (GRIOTTE__BUILD_STRICT)
    if (NOT CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 17)
    endif()

    set(CXX_STANDARD_REQUIRED ON)
    set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++XX rather than -std=gnu++XX
endif()

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

set(FETCHCONTENT_UPDATES_DISCONNECTED_CMRC ON)

add_subdirectory(3rdparty)
add_subdirectory(2ndparty)
include(${CMAKE_CURRENT_LIST_DIR}/library.cmake)

if (GRIOTTE__BUILD_TESTS AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/tests)
    enable_testing()
    add_subdirectory(tests)
endif()

if (GRIOTTE__BUILD_DEMO AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/demo)
    add_subdirectory(demo)
endif()

include(GNUInstallDirs)

install(TARGETS griotte
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
