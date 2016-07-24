cmake_minimum_required(VERSION 3.3)
project(haha)

set(CMAKE_C_FLAGS "${CMAKE_CXX_FLAGS} -std=c++98")

set(SOURCE_FILES main.cpp)
add_executable(haha ${SOURCE_FILES})