################################################################################
# Copyright (c) 2021 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
################################################################################
cmake_minimum_required (VERSION 3.11)

set(LESSONS
    glfw-lesson01
    glfw-lesson02
    glfw-lesson03-FPS
    glfw-lesson04-Monitor
    glfw-lesson05-FontInfo
    glfw-lesson06-Shader
    glfw-lesson07-Text)

    if (TARGET pfs::griotte)
        set(_griotte_lib pfs::griotte)
    elseif (TARGET pfs::griotte::static)
        set(_griotte_lib pfs::griotte::static)
    endif()

foreach (_lesson ${LESSONS})
    file(GLOB SOURCES ${_lesson}/*.cpp)
    add_executable(${_lesson} ${SOURCES})
    target_link_libraries(${_lesson} PRIVATE pfs::common ${_griotte_lib})
    target_include_directories(${_lesson} PRIVATE ${CMAKE_CURRENT_LIST_DIR}
            $<TARGET_PROPERTY:glfw,INTERFACE_INCLUDE_DIRECTORIES>)

    add_dependencies(${_lesson} glfw-ep)
endforeach()

# Copy test files to build folder
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

