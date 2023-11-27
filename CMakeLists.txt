cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 98)

add_executable(untitled src/main.cpp
        src/CNode.h
        src/CNode.cpp
        src/CTree.h
        src/CTree.cpp
        src/Utilities.cpp)
