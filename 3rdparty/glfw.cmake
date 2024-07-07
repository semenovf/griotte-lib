####################################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte`.
#
# Changelog:
#      2024.07.02 Initial version.
####################################################################################################
project(glfw-ep C CXX)

include(ExternalProject)

set(_bin_dir "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(_src_dir "${CMAKE_CURRENT_LIST_DIR}/glfw")

ExternalProject_Add(${PROJECT_NAME}
    SOURCE_DIR ${_src_dir}
    CMAKE_ARGS
        -DBUILD_SHARED_LIBS=ON
        -DGLFW_BUILD_EXAMPLES=OFF
        -DGLFW_BUILD_TESTS=OFF
        -DGLFW_BUILD_DOCS=OFF
        -DGLFW_INSTALL=ON
        -DCMAKE_PREFIX_PATH:PATH="${_bin_dir}"
        --install-prefix ${_bin_dir}
    BUILD_IN_SOURCE FALSE)

file(MAKE_DIRECTORY "${_bin_dir}/include")

add_library(glfw SHARED IMPORTED GLOBAL)
set_target_properties(glfw PROPERTIES
    IMPORTED_LOCATION "${_bin_dir}/lib/libglfw.so"
    INTERFACE_INCLUDE_DIRECTORIES "${_bin_dir}/include")
