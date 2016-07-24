cmake_minimum_required(VERSION 3.0)

project(student C)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.c)


find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})
# Add other flags to the compiler
add_definitions(${GTK3_CFLAGS_OTHER})
# Add an executable compiled from hello.c
add_executable(student main.c)
# Link the target to the GTK+ libraries
target_link_libraries(student ${GTK3_LIBRARIES})

add_executable(list_demo demo.c)
# Link the target to the GTK+ libraries
target_link_libraries(list_demo ${GTK3_LIBRARIES})
