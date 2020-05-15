cmake_minimum_required (VERSION 3.1)

set(LESSONS
    glfw-lesson01
    glfw-lesson02
    glfw-lesson03-FPS
    glfw-lesson04-Monitor
    glfw-lesson05-FontInfo
    glfw-lesson06-Shader
    glfw-lesson07-Text)

foreach (lesson ${LESSONS})
    file(GLOB SOURCES ${lesson}/*.cpp)
    add_executable(${lesson} ${SOURCES})
    target_link_libraries(${lesson} pfs-griotte)
    target_include_directories(${lesson} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

    set_target_properties(${lesson}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endforeach()
