################################################################################
# Copyright (c) 2024-2025 Vladislav Trifochkin
#
# This file is part of `griotte-lib`.
#
# Changelog:
#      2024.07.15 Initial version.
################################################################################
project(griotte-TESTS CXX C)

set(TESTS layout)

foreach (target ${TESTS})
    add_executable(tests-${target} ${target}.cpp)
    target_link_libraries(tests-${target} PRIVATE pfs::griotte)
    add_test(NAME tests-${target} COMMAND tests-${target})
endforeach()
