cmake_minimum_required(VERSION 3.3)
project(OneginSorting)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(OneginSorting ${SOURCE_FILES})