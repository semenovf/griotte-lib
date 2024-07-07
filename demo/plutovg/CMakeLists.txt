################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.07.03 Initial version.
################################################################################
project(smiley C)
add_executable(${PROJECT_NAME} smiley.c)
target_link_libraries(${PROJECT_NAME} plutovg)
