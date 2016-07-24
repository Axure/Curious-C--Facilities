cmake_minimum_required(VERSION 3.4)
project(Ax_pp_Lib_Custom)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(Ax_pp_Lib_Custom
        ${SOURCE_FILES}
        binomial_heap.tcc
        )