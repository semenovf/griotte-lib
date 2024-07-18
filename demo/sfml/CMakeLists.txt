################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.07.12 Initial version.
################################################################################
project(sfml-demo CXX C)

if (TARGET pfs::griotte)
    set(_griotte_lib pfs::griotte)
elseif (TARGET pfs::griotte::static)
    set(_griotte_lib pfs::griotte::static)
else()
    message(FATAL_ERROR "No any griotte TARGET found")
endif()

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${_griotte_lib})
