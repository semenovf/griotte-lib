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

option(GRIOTTE__BUILD_SHARED "Enable build shared library" OFF)
option(GRIOTTE__BUILD_STATIC "Enable build static library" ON)
option(GRIOTTE__SDL2_BACKEND "Enable SDL2 backend" OFF)
option(GRIOTTE__SFML_BACKEND "Enable SFML backend" ON)

if (NOT PORTABLE_TARGET__CURRENT_PROJECT_DIR)
    set(PORTABLE_TARGET__CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR})
endif()

if (GRIOTTE__BUILD_SHARED)
    portable_target(ADD_SHARED ${PROJECT_NAME} ALIAS pfs::griotte EXPORTS GRIOTTE__EXPORTS)
    list(APPEND _griotte__targets ${PROJECT_NAME})
endif()

if (GRIOTTE__BUILD_STATIC)
    set(STATIC_PROJECT_NAME ${PROJECT_NAME}-static)
    portable_target(ADD_STATIC ${STATIC_PROJECT_NAME} ALIAS pfs::griotte::static EXPORTS GRIOTTE__STATIC)
    list(APPEND _griotte__targets ${PROJECT_NAME}-static)
endif()

if (NOT TARGET pfs::common)
    portable_target(INCLUDE_PROJECT
        ${PORTABLE_TARGET__CURRENT_PROJECT_DIR}/2ndparty/common/library.cmake)
endif()

list(APPEND _griotte__sources
    ${CMAKE_CURRENT_LIST_DIR}/src/fixed_layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/layout.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/node.cpp)

if (GRIOTTE__SDL2_BACKEND)
    list(APPEND _griotte__sources ${CMAKE_CURRENT_LIST_DIR}/src/SDL2/gui.cpp)
endif()

if (GRIOTTE__SFML_BACKEND)
    list(APPEND _griotte__sources
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/ui.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/font.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/rectangle.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/text.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/SFML/RoundedRectangleShape.cpp)
endif()

foreach(_target IN LISTS _griotte__targets)
    portable_target(SOURCES ${_target} ${_griotte__sources})
    portable_target(INCLUDE_DIRS ${_target} PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/include
        ${CMAKE_CURRENT_LIST_DIR}/include/pfs)
    portable_target(LINK ${_target} PUBLIC pfs::common)

    if (GRIOTTE__SDL2_BACKEND)
        add_dependencies(${_target} SDL2-ep SDL2)
        portable_target(LINK ${_target} PUBLIC $<TARGET_PROPERTY:SDL2,INTERFACE_LINK_LIBRARIES>)
        portable_target(INCLUDE_DIRS ${_target} PUBLIC $<TARGET_PROPERTY:SDL2,INTERFACE_INCLUDE_DIRECTORIES>)
    endif()

    if (GRIOTTE__SFML_BACKEND)
        add_dependencies(${_target} SFML-ep SFML)
        portable_target(LINK ${_target} PUBLIC $<TARGET_PROPERTY:SFML,INTERFACE_LINK_LIBRARIES>)
        portable_target(INCLUDE_DIRS ${_target} PUBLIC $<TARGET_PROPERTY:SFML,INTERFACE_INCLUDE_DIRECTORIES>)
        target_link_directories(${_target} PUBLIC $<TARGET_PROPERTY:SFML,INTERFACE_LINK_DIRECTORIES>)
    endif()
endforeach()
