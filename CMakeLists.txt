cmake_minimum_required (VERSION 3.1)
project(pfs-griotte CXX)

option(${PROJECT_NAME}_BUILD_TESTS "Build tests" ON)

# Prefer GLVND (new behaviour) over LEGACY
cmake_policy(SET CMP0072 NEW)
find_package(OpenGL REQUIRED)

message(STATUS "OpenGL libraries   : ${OPENGL_LIBRARIES}")
message(STATUS "OpenGL include dirs: ${OPENGL_INCLUDE_DIR}")
message(STATUS "OpenGL GLU found   : ${OPENGL_GLU_FOUND}")
message(STATUS "OpenGL GLX found   : ${OpenGL_GLX_FOUND}")
message(STATUS "OpenGL EGL found   : ${OpenGL_EGL_FOUND}")
message(STATUS "OpenGL XMESA found : ${OPENGL_XMESA_FOUND}")

# include_directories(${CMAKE_CURRENT_LIST_DIR}/include
#     ${CMAKE_CURRENT_LIST_DIR}/pfs-common/include
#     ${CMAKE_CURRENT_LIST_DIR}/3rdparty/freetype2/include
#     ${CMAKE_CURRENT_LIST_DIR}/3rdparty/glfw/include)

################################################################################
# GLFW build
################################################################################
add_subdirectory(3rdparty/glfw)

################################################################################
# Freetype2 build
################################################################################
set(SKIP_INSTALL_ALL ON)
set(CMAKE_DISABLE_FIND_PACKAGE_ZLIB TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BZip2 TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_PNG TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_HarfBuzz TRUE)
set(CMAKE_DISABLE_FIND_PACKAGE_BrotliDec TRUE)
add_subdirectory(3rdparty/freetype2)

add_subdirectory(src)
add_subdirectory(demo)

set_target_properties(
    glfw
    PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")


if (${PROJECT_NAME}_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
