cmake_minimum_required(VERSION 4.3)
project(Project_2___Cogwork_Engineers)

set(CMAKE_CXX_STANDARD 14)

include_directories(src)

add_executable(Project_2___Cogwork_Engineers
        src/bPlus.cpp
        src/bPlus.h
        src/DataHeap.cpp
        src/DataHeap.h
        src/DataPoint.cpp
        src/DataPoint.h
        src/main.cpp)
