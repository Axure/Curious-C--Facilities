cmake_minimum_required(VERSION 3.4)
project(MetaParsers__)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp RegexpParser.cpp RegexpParser.h)
add_executable(MetaParsers__ ${SOURCE_FILES})