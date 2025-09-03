cmake_minimum_required(VERSION 3.26)

project(2048 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(2048
  main.cpp

  Engine/Engine.cpp
  Engine/Engine.hpp
  Engine/Gameboard.cpp
  Engine/Gameboard.hpp
)
