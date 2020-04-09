cmake_minimum_required (VERSION 3.1)

set(LESSONS
    glfw-lesson01)

foreach (lesson ${LESSONS})
    file(GLOB SOURCES ${lesson}/*.cpp)
    add_executable(${lesson} ${SOURCES})
    target_link_libraries(${lesson} glfw OpenGL::GLU OpenGL::GL)

    set_target_properties(${lesson}
        PROPERTIES
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
endforeach()
