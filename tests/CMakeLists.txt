# This is the "object library" target: compiles the sources only once
#add_library(CATCH2_OBJLIB OBJECT catch2-main.cpp)
add_library(doctest_OBJLIB OBJECT doctest-main.cpp)

# Optional: shared libraries need PIC
#set_property(TARGET CATCH2_OBJLIB PROPERTY POSITION_INDEPENDENT_CODE 1)
set_property(TARGET doctest_OBJLIB PROPERTY POSITION_INDEPENDENT_CODE 1)

# Add unit test targets
list(APPEND test_targets point)
#list(APPEND MY_TEST_TARGETS line)
#list(APPEND MY_TEST_TARGETS rect)
#list(APPEND MY_TEST_TARGETS indents)
#list(APPEND MY_TEST_TARGETS path)

# Porcess all unit test targets
foreach(test ${test_targets})
    if(${test}_SOURCES)
        add_executable(${test} ${${test}_SOURCES} $<TARGET_OBJECTS:doctest_OBJLIB>)
    else()
        add_executable(${test} ${test}.cpp $<TARGET_OBJECTS:doctest_OBJLIB>)
    endif()

    add_test(NAME ${test} COMMAND ${test})
endforeach()
