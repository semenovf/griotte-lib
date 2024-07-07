####################################################################################################
# Copyright (c) 2024 Vladislav Trifochkin
#
# This file is part of `griotte`.
#
# Changelog:
#      2024.07.03 Initial version.
####################################################################################################
project(plutovg LANGUAGES C)

add_library(${PROJECT_NAME} SHARED)
target_sources(${PROJECT_NAME} PRIVATE
    plutovg/source/plutovg-paint.c
    plutovg/source/plutovg-matrix.c
    plutovg/source/plutovg-path.c
    plutovg/source/plutovg-font.c
    plutovg/source/plutovg-surface.c
    plutovg/source/plutovg-canvas.c
    plutovg/source/plutovg-rasterize.c
    plutovg/source/plutovg-blend.c
    plutovg/source/plutovg-ft-raster.c
    plutovg/source/plutovg-ft-stroker.c
    plutovg/source/plutovg-ft-math.c)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/plutovg/include"
    PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/plutovg/source"
    "${CMAKE_CURRENT_SOURCE_DIR}/plutovg/stb")

target_compile_definitions(${PROJECT_NAME} PRIVATE PLUTOVG_BUILD=1)
target_link_libraries(${PROJECT_NAME} PRIVATE m)
