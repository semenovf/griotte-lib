################################################################################
# Copyright (c) 2024-2025 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.06.05 Initial version.
#      2025.06.24 Min CMake version is 3.19.
################################################################################
cmake_minimum_required (VERSION 3.19)
project(griotte LANGUAGES CXX C)

if (GRIOTTE__BUILD_SHARED)
    add_library(griotte SHARED)
    target_compile_definitions(griotte PRIVATE GRIOTTE__EXPORTS)
else()
    add_library(griotte STATIC)
    target_compile_definitions(griotte PUBLIC GRIOTTE__STATIC)
endif()

add_library(pfs::griotte ALIAS griotte)

if (MSVC)
    target_compile_definitions(griotte PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

target_sources(griotte PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/anchors_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/circle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/fixed_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/linear_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/node.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/resources/fonts/roboto_regular.c
    ${CMAKE_CURRENT_LIST_DIR}/src/resources/fonts/inter_regular.c)

if (GRIOTTE__SFML_BACKEND)
    target_sources(griotte PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/ui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/circle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/font.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/image.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/rectangle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/text.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/RoundedRectangleShape.cpp)
endif()

if (GRIOTTE__SFML_BACKEND)
    target_link_libraries(griotte PUBLIC sfml-graphics sfml-system sfml-window)
    # target_include_directories(griotte PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SFML/include)
endif()

target_include_directories(griotte
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pfs/griotte
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pfs)
target_link_libraries(griotte PUBLIC pfs::common)
