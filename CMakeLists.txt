cmake_minimum_required(VERSION 3.26)
project(untitled)

set(CMAKE_CXX_STANDARD 98)

add_executable(untitled main.cpp
        CNode.h
        CNode.cpp
        CTree.h
        CTree.cpp
        Utilities.cpp)
