cmake_minimum_required(VERSION 3.5)
project(TypeScriptVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(TypeScriptVM ${SOURCE_FILES})