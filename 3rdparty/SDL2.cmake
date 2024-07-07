####################################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte`.
#
# Changelog:
#      2024.07.06 Initial version.
####################################################################################################
project(SDL2-ep C CXX)

include(ExternalProject)

set(_build_type Debug)
set(_bin_dir "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(_src_dir "${CMAKE_CURRENT_LIST_DIR}/SDL2")
set(_install_dir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if (_build_type STREQUAL "Debug")
    set(_lib_name libSDL2d.so)
else()
    set(_lib_name libSDL2.so)
endif()

ExternalProject_Add(${PROJECT_NAME}
    SOURCE_DIR ${_src_dir}
    BINARY_DIR ${_bin_dir}
    # INSTALL_DIR ${_install_dir} # This option not work properly for installation stage
    CMAKE_ARGS
        -DSDL_SHARED=ON
        -DSDL_STATIC=OFF
        -DSDL_TEST=OFF
        -DSDL_INSTALL_TESTS=OFF
        -DCMAKE_BUILD_TYPE=${_build_type}
        # -DCMAKE_PREFIX_PATH:PATH="${_install_dir}" # This option not work properly for installation stage
        --install-prefix ${_install_dir} # This option work properly for installation stage
                                         # Not need to `file(MAKE_DIRECTORY "${_install_dir}/include")`
    BUILD_IN_SOURCE FALSE
    BUILD_BYPRODUCTS "${_install_dir}/lib/${_lib_name}") # <= Fixes 'output/lib/libSDL2.so', needed by 'output/sdl2-demo', missing and no known rule to make it

add_library(SDL2 SHARED IMPORTED GLOBAL)
set_target_properties(SDL2 PROPERTIES
    # IMPORTED_LOCATION "${_install_dir}/lib/libSDL2.so"
    INTERFACE_LINK_LIBRARIES "${_install_dir}/lib/${_lib_name}"
    INTERFACE_INCLUDE_DIRECTORIES "${_install_dir}/include")
add_dependencies(SDL2 ${PROJECT_NAME})
