################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.07.12 Initial version.
################################################################################
project(sfml-demo CXX C)

cmrc_add_resource_library(griotte-rc-icons
    ALIAS rc::icons
    NAMESPACE griotte
    TYPE STATIC
    WHENCE resources/icons
    PREFIX icons
    resources/icons/griotte-cherry-24.png
    resources/icons/griotte-cherry-48.png
    resources/icons/griotte-cherry-96.png
    resources/icons/griotte-cherry-v1.png
    resources/icons/griotte-cherry-v2.png)

add_executable(${PROJECT_NAME}
    main.cpp
    anchors_layout.cpp
    fixed_layout.cpp
    palette.cpp
    scale.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE pfs::griotte rc::icons)

get_property(_runtime_output_directory GLOBAL PROPERTY RUNTIME_OUTPUT_DIRECTORY)

if (NOT _runtime_output_directory)
    message(FATAL_ERROR "_runtime_output_directory NOT SET")
endif()

add_custom_command(TARGET ${PROJECT_NAME}
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../../resources/fonts/Inter.ttf ${_runtime_output_directory}/Inter.ttf
    COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_LIST_DIR}/../../resources/fonts/Roboto-Regular.ttf ${_runtime_output_directory}/Roboto-Regular.ttf
    VERBATIM)
