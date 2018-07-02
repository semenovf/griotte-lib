cmake_minimum_required (VERSION 3.1)
#project(pfs-griotte CXX)

#enable_testing()

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(src)
add_subdirectory(tests)
