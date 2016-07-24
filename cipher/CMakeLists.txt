cmake_minimum_required(VERSION 3.5)
project(cipher)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(SOURCE_FILES main.cpp client.cpp BlowFish.cc BlowFish.hh wait.h)
add_executable(cipher ${SOURCE_FILES})
target_link_libraries(cipher ws2_32)

add_executable(winsock_client client.cpp)
target_link_libraries(winsock_client ws2_32 mswsock advapi32)

add_executable(winsock_server server.cpp)
target_link_libraries(winsock_server ws2_32)

add_executable(file_and_memory file_and_memory.cpp)

add_subdirectory(googletest)

add_executable(file_and_memory_test file_and_memory_test.cpp)
target_link_libraries(file_and_memory_test gtest gtest_main)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

add_library(MiniFS MiniFS.cpp MiniFS.h)

add_executable(Wait wait.cpp wait.h)