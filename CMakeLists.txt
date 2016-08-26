cmake_minimum_required(VERSION 3.3)
project(basic)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES combination.cpp)
add_executable(basic ${SOURCE_FILES})