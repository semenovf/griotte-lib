################################################################################
# Copyright (c) 2019-2020 Vladislav Trifochkin
#
# This file is part of [pfs-griotte](https://github.com/semenovf/pfs-griotte) library.
#
# Changelog:
#      2020.04.26 Initial version
################################################################################

add_library(pfs-griotte INTERFACE)
target_link_libraries(pfs-griotte INTERFACE freetype glfw OpenGL::GLU OpenGL::GL)
target_include_directories(pfs-griotte INTERFACE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/pfs-common/include
    ${CMAKE_SOURCE_DIR}/3rdparty/freetype2/include
    ${CMAKE_SOURCE_DIR}/3rdparty/glfw/include)
