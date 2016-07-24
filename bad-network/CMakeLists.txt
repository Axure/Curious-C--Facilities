cmake_minimum_required(VERSION 3.5)
project(bad_network)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(bad_network ${SOURCE_FILES})