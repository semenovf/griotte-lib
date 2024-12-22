################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.06.05 Initial version.
################################################################################
cmake_minimum_required (VERSION 3.11)
project(griotte LANGUAGES CXX C)

if (GRIOTTE__BUILD_SHARED)
    add_library(griotte SHARED)
    target_compile_definitions(griotte PRIVATE IONIK__EXPORTS)
else()
    add_library(griotte STATIC)
    target_compile_definitions(griotte PUBLIC IONIK__STATIC)
endif()

add_library(pfs::griotte ALIAS griotte)

if (MSVC)
    target_compile_definitions(ionik PRIVATE _CRT_SECURE_NO_WARNINGS)
endif()

target_sources(griotte PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src/anchors_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/circle.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/fixed_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/linear_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/node.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/resources/fonts/roboto_regular.c)

if (GRIOTTE__SFML_BACKEND)
    target_sources(griotte PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/ui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/circle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/font.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/font_resources.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/image.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/rectangle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/text.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/RoundedRectangleShape.cpp)
endif()


if (NOT TARGET pfs::common)
    set(FETCHCONTENT_UPDATES_DISCONNECTED_COMMON ON)

    message(STATUS "Fetching pfs::common ...")
    include(FetchContent)
    FetchContent_Declare(common
        GIT_REPOSITORY https://github.com/semenovf/common-lib.git
        GIT_TAG master
        GIT_PROGRESS TRUE
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/2ndparty/common
        SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/2ndparty/common)
    FetchContent_MakeAvailable(common)
    message(STATUS "Fetching pfs::common complete")
endif()

if (GRIOTTE__SFML_BACKEND)
    set(FETCHCONTENT_UPDATES_DISCONNECTED_SFML ON)

    set(SFML_BUILD_WINDOW TRUE CACHE BOOL "")
    set(SFML_BUILD_GRAPHICS TRUE CACHE BOOL "")
    set(SFML_BUILD_AUDIO FALSE CACHE BOOL "")
    set(SFML_BUILD_NETWORK FALSE CACHE BOOL "")
    set(SFML_BUILD_DOC FALSE CACHE BOOL "")
    set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "")
    set(SFML_BUILD_TEST_SUITE FALSE CACHE BOOL "")

    message(STATUS "Fetching SFML ...")
    include(FetchContent)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        GIT_PROGRESS TRUE
        GIT_SHALLOW 1
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SFML
        SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/3rdparty/SFML)
    FetchContent_MakeAvailable(SFML)
    message(STATUS "Fetching SFML complete")

    target_link_libraries(griotte PUBLIC sfml-graphics sfml-system sfml-window)
    target_include_directories(griotte PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/3rdparty/SFML/include)
endif()

target_include_directories(griotte
    PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pfs/griotte
    PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include/pfs)
target_link_libraries(griotte PUBLIC pfs::common)
