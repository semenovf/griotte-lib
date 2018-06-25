cmake_minimum_required (VERSION 3.1)

project(pfs-griotte CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(SOURCES
    src/main.cpp
    src/MainWindow.cpp
    src/Surface.cpp)

add_executable(griotte ${SOURCES})
target_link_libraries(griotte Qt5::Widgets)
