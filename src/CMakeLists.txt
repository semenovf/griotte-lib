set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SOURCES
    main.cpp
    MainWindow.cpp
    Surface.cpp)

add_executable(griotte ${SOURCES})
target_link_libraries(griotte Qt5::Widgets)