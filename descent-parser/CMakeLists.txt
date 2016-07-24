cmake_minimum_required(VERSION 3.5)
project(descent_parser)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c lexer.c)
add_executable(descent_parser ${SOURCE_FILES})