cmake_minimum_required(VERSION 3.4)
project(StaticTypedLang)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp Source/Lang/Semantics/Axiom.cpp Source/Lang/Semantics/Axiom.hpp Source/Lang/Basics/Macros.hpp Source/Lang/Basics/Object.cpp Source/Lang/Basics/Object.hpp Source/Lang/Lexics/Token.cpp Source/Lang/Lexics/Token.hpp Source/Lang/Lexics/Keyword.cpp Source/Lang/Lexics/Keyword.hpp Source/Lang/Semantics/Template.cpp Source/Lang/Semantics/Template.hpp)
add_executable(StaticTypedLang ${SOURCE_FILES})