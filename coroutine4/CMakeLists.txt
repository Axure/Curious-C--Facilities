cmake_minimum_required(VERSION 3.5)
project(coroutine4)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(coroutine4 ${SOURCE_FILES})

add_executable(coroutine4_test_jmp test_jmp.cpp)