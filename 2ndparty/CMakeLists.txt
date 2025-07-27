################################################################################
# Copyright (c) 2025 Vladislav Trifochkin
#
#  This file is part of `griotte-lib`.
#
# Changelog:
#       2025.06.24 Initial version.
#       2025.07.27 Fixed fetching dependencies.
################################################################################

include(FetchContent)

foreach (_dep common)
    if (NOT TARGET ${_dep})
        if (GRIOTTE__DISABLE_FETCH_CONTENT AND EXISTS ${CMAKE_CURRENT_LIST_DIR}/${_dep}/.git)
            add_subdirectory(${_dep})
        else()
            message(STATUS "Fetching ${_dep} ...")
            FetchContent_Declare(${_dep}
                GIT_REPOSITORY git@github.com:semenovf/${_dep}-lib.git
                GIT_TAG master
                SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/${_dep})
            FetchContent_MakeAvailable(${_dep})
            message(STATUS "Fetching ${_dep} complete")
        endif()
    endif()
endforeach()
