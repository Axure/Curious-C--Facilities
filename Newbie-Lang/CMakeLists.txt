cmake_minimum_required(VERSION 3.3)
project(Newbie_Lang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES src/main/cpp/main.cpp src/main/cpp/Parser.cpp src/main/cpp/Parser.h src/main/cpp/StateMachine.cpp src/main/cpp/StateMachine.h)
add_executable(Newbie_Lang ${SOURCE_FILES})