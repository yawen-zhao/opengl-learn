cmake_minimum_required(VERSION 3.10)

project(demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Debug)
add_definitions(-g)

add_subdirectory(src)
