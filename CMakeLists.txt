cmake_minimum_required(VERSION 3.14)
project(COP2001ProceduralProject)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++")
set(SOURCE_FILES main.cpp)
add_executable(COP2001ProceduralProject main.cpp prototypes.h sha256.cpp sha256.h)