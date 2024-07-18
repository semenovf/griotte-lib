####################################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte`.
#
# Changelog:
#      2024.07.12 Initial version.
####################################################################################################
project(SFML-ep C CXX)

include(ExternalProject)

set(_build_type Debug)
set(_bin_dir "${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}")
set(_src_dir "${CMAKE_CURRENT_LIST_DIR}/SFML")
set(_install_dir "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

if (_build_type STREQUAL "Debug")
    set(_lib_name_graphics libsfml-graphics-d.so)
    set(_lib_name_system libsfml-system-d.so)
    set(_lib_name_window libsfml-window-d.so)
else()
    set(_lib_name_graphics libsfml-graphics.so)
    set(_lib_name_system libsfml-system.so)
    set(_lib_name_window libsfml-window.so)
endif()

ExternalProject_Add(${PROJECT_NAME}
    SOURCE_DIR ${_src_dir}
    BINARY_DIR ${_bin_dir}
    # INSTALL_DIR ${_install_dir} # This option not work properly for installation stage
    CMAKE_ARGS
        -DBUILD_SHARED_LIBS:BOOL=TRUE
        -DSFML_BUILD_WINDOW:BOOL=TRUE
        -DSFML_BUILD_GRAPHICS:BOOL=TRUE
        -DSFML_BUILD_AUDIO:BOOL=FALSE
        -DSFML_BUILD_NETWORK:BOOL=FALSE
        -DSFML_BUILD_DOC:BOOL=FALSE
        -DSFML_BUILD_EXAMPLES:BOOL=FALSE
        -DSFML_BUILD_TEST_SUITE:BOOL=FALSE
        -DCMAKE_BUILD_TYPE=${_build_type}
        # -DCMAKE_PREFIX_PATH:PATH="${_install_dir}" # This option not work properly for installation stage
        --install-prefix ${_install_dir} # This option work properly for installation stage
                                         # Not need to `file(MAKE_DIRECTORY "${_install_dir}/include")`
    BUILD_IN_SOURCE FALSE
    BUILD_BYPRODUCTS
        "${_install_dir}/lib/${_lib_name_graphics}"
        "${_install_dir}/lib/${_lib_name_system}"
        "${_install_dir}/lib/${_lib_name_window}")

add_library(SFML SHARED IMPORTED GLOBAL)
set_target_properties(SFML PROPERTIES
    INTERFACE_LINK_LIBRARIES
        "${_lib_name_graphics};${_lib_name_system};${_lib_name_window}"
    INTERFACE_LINK_DIRECTORIES "${_install_dir}/lib"
    INTERFACE_INCLUDE_DIRECTORIES "${_install_dir}/include")
add_dependencies(SFML ${PROJECT_NAME})
