cmake_minimum_required(VERSION 3.5)
project(symmetry)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)
add_executable(symmetry ${SOURCE_FILES})
add_executable(another another.c)