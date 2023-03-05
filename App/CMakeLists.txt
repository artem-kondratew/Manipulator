cmake_minimum_required(VERSION 3.25)
project(Manipulator)

set(CMAKE_CXX_STANDARD 20)

add_executable(Manipulator main.cpp ../Config.h Graphics.h Connect.cpp)

set(CMAKE_CXX_FLAGS "-lncurses")