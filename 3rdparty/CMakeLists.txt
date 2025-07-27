################################################################################
# Copyright (c) 2025 Vladislav Trifochkin
#
#  This file is part of `griotte-lib`.
#
# Changelog:
#       2025.06.24 Initial version.
################################################################################

if (GRIOTTE__DISABLE_FETCH_CONTENT AND EXISTS cmrc/.git)
    add_subdirectory(cmrc 3rdparty/cmrc)
else()
    message(STATUS "Fetching cmrc ...")
    include(FetchContent)
    FetchContent_Declare(cmrc
        GIT_REPOSITORY https://github.com/vector-of-bool/cmrc.git
        GIT_TAG master
        GIT_PROGRESS TRUE
        GIT_SHALLOW 1
        SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/cmrc
        SUBBUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/cmrc)
    FetchContent_MakeAvailable(cmrc)
    message(STATUS "Fetching cmrc complete")
endif()

if (GRIOTTE__SFML_BACKEND)
    if (GRIOTTE__DISABLE_FETCH_CONTENT AND EXISTS SFML/.git)
        add_subdirectory(SFML 3rdparty/SFML)
    else()
        set(FETCHCONTENT_UPDATES_DISCONNECTED_SFML ON)

        set(SFML_BUILD_WINDOW TRUE CACHE BOOL "")
        set(SFML_BUILD_GRAPHICS TRUE CACHE BOOL "")
        set(SFML_BUILD_AUDIO FALSE CACHE BOOL "")
        set(SFML_BUILD_NETWORK FALSE CACHE BOOL "")
        set(SFML_BUILD_DOC FALSE CACHE BOOL "")
        set(SFML_BUILD_EXAMPLES FALSE CACHE BOOL "")
        set(SFML_BUILD_TEST_SUITE FALSE CACHE BOOL "")

        message(STATUS "Fetching SFML ...")
        include(FetchContent)
        FetchContent_Declare(SFML
            GIT_REPOSITORY https://github.com/SFML/SFML.git
            GIT_TAG 2.6.2
            GIT_PROGRESS TRUE
            GIT_SHALLOW 1
            SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML)
        FetchContent_MakeAvailable(SFML)
        message(STATUS "Fetching SFML complete")
    endif()
endif(GRIOTTE__SFML_BACKEND)
