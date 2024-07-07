################################################################################
# Copyright (c) 2021 Vladislav Trifochkin
#
# This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
################################################################################
cmake_minimum_required (VERSION 3.5)
project(pfs-griotte CXX)

string(REPLACE "-" "::" _project_alias ${PROJECT_NAME})
set(_project_basename ${PROJECT_NAME})

option(${PROJECT_NAME}_BUILD_TESTS "Build tests" OFF)
option(${PROJECT_NAME}_BUILD_DEMO "Build demo" OFF)

# Prefer GLVND (new behaviour) over LEGACY
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

message(STATUS "C++ compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "C++ compiler version: ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "Project alias: ${_project_alias}")

message(STATUS "OpenGL libraries   : ${OPENGL_LIBRARIES}")
message(STATUS "OpenGL include dirs: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL GLU found   : ${OPENGL_GLU_FOUND}")
message(STATUS "OpenGL GLX found   : ${OpenGL_GLX_FOUND}")
message(STATUS "OpenGL EGL found   : ${OpenGL_EGL_FOUND}")
message(STATUS "OpenGL XMESA found : ${OPENGL_XMESA_FOUND}")

set(CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF) # use -std=c++XX rather than -std=gnu++XX

################################################################################
# GLFW build
################################################################################
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW example programs")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW test programs")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build the GLFW documentation")
set(GLFW_INSTALL OFF CACHE BOOL "Generate installation target")
set(GLFW_VULKAN_STATIC OFF CACHE BOOL "Assume the Vulkan loader is linked with the application")
add_subdirectory(3rdparty/glfw)

################################################################################
# Freetype2 build
################################################################################
set(SKIP_INSTALL_ALL ON)
set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BrotliDec TRUE)
add_subdirectory(3rdparty/freetype2)

add_subdirectory(src)

if (${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if (${PROJECT_NAME}_BUILD_DEMO)
    add_subdirectory(demo)
endif()
