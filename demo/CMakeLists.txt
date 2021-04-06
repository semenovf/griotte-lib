################################################################################
# Copyright (c) 2021 Vladislav Trifochkin
#
# This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
################################################################################
cmake_minimum_required (VERSION 3.5)

set(LESSONS
    glfw-lesson01
    glfw-lesson02
    glfw-lesson03-FPS
    glfw-lesson04-Monitor
    glfw-lesson05-FontInfo
    glfw-lesson06-Shader
    glfw-lesson07-Text)

foreach (lesson ${LESSONS})
    file(GLOB SOURCES ${lesson}/*.cpp)
    add_executable(${lesson} ${SOURCES})
    target_link_libraries(${lesson} pfs-griotte)
    target_include_directories(${lesson} PRIVATE ${CMAKE_CURRENT_LIST_DIR})
endforeach()

# Copy test files to build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

