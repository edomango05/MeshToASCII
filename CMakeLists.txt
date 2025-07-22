cmake_minimum_required(VERSION 3.31)
project(cube)

set(CMAKE_CXX_STANDARD 20)

add_executable(cube main.cpp
        linear.h
        buffers.h
        parser.h)
