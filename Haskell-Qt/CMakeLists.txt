cmake_minimum_required(VERSION 3.0)
project(Haskell_Qt)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_PREFIX_PATH  "E:\\msys64_right\\mingw64\\qt5-static\\lib\\cmake\\Qt5Widgets\\")

set(SOURCE_FILES main.cpp src/termops.c src/termops.h)
add_executable(Haskell_Qt ${SOURCE_FILES})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

# Find the QtWidgets library
find_package(Qt5Widgets REQUIRED)

# Use the Widgets module from Qt 5.
target_link_libraries(Haskell_Qt Qt5::Widget)

add_executable(VirtualFunction VirtualFunction.cpp)