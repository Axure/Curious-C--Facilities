cmake_minimum_required(VERSION 3.4)
project(TypedVM)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Source/TypedVm/TypedVm.cpp Source/TypedVm/TypedVm.h Source/TypedVm/Macros.h Source/TypedVm/FiniteStateMachine.h Source/TypedVm/Basics/Object.cpp Source/TypedVm/Basics/Object.hpp Source/TypedVm/Semantics/Class.cpp Source/TypedVm/Semantics/Class.hpp Source/TypedVm/ClassInstance.cpp Source/TypedVm/ClassInstance.h Source/TypedVm/Semantics/Type.cpp Source/TypedVm/Semantics/Type.hpp Source/TypedVm/Semantics/Interface.cpp Source/TypedVm/Semantics/Interface.hpp)
add_executable(TypedVM ${SOURCE_FILES})