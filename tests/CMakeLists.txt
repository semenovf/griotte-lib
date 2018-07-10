#project(pfs-griotte-tests CXX)
enable_testing()

# This is the "object library" target: compiles the sources only once
add_library(CATCH2_OBJLIB OBJECT catch2-main.cpp)
# Optional: shared libraries need PIC
set_property(TARGET CATCH2_OBJLIB PROPERTY POSITION_INDEPENDENT_CODE 1)

# Add unit test targets
list(APPEND MY_TEST_TARGETS indents)
list(APPEND MY_TEST_TARGETS rect)

# Porcess all unit test targets
foreach(MY_TEST_TARGET ${MY_TEST_TARGETS})
    if(${MY_TEST_TARGET}_SOURCES)
        add_executable(${MY_TEST_TARGET} ${${MY_TEST_TARGET}_SOURCES} $<TARGET_OBJECTS:CATCH2_OBJLIB>)
    else()
        add_executable(${MY_TEST_TARGET} ${MY_TEST_TARGET}.cpp $<TARGET_OBJECTS:CATCH2_OBJLIB>)
    endif()

    add_test(NAME ${MY_TEST_TARGET} COMMAND ${MY_TEST_TARGET})
endforeach(MY_TEST_TARGET)
