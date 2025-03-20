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
    WHENCE ${CMAKE_SOURCE_DIR}/../resources/icons
    PREFIX icons
    ${CMAKE_SOURCE_DIR}/../resources/icons/griotte-cherry-24.png
    ${CMAKE_SOURCE_DIR}/../resources/icons/griotte-cherry-48.png
    ${CMAKE_SOURCE_DIR}/../resources/icons/griotte-cherry-96.png
    ${CMAKE_SOURCE_DIR}/../resources/icons/griotte-cherry-v1.png
    ${CMAKE_SOURCE_DIR}/../resources/icons/griotte-cherry-v2.png)

add_executable(${PROJECT_NAME}
    main.cpp
    anchors_layout.cpp
    fixed_layout.cpp
    palette.cpp
    scale.cpp
    text_input.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE pfs::griotte rc::icons)
