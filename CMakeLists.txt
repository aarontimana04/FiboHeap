cmake_minimum_required(VERSION 3.26)
project(fiboheap)

set(CMAKE_CXX_STANDARD 17)

add_executable(fiboheap main.cpp
        Node.cpp
        Node.h
        FiboHeap.cpp
        FiboHeap.h)
