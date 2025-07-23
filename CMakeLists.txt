cmake_minimum_required(VERSION 3.31)
project(MeshToASCII)

set(CMAKE_CXX_STANDARD 20)

include_directories(src/include)

add_executable(m2ascii
        src/main.cpp
        src/include/linear.h
        src/include/buffers.h
        src/include/parser.h
        src/implementation/buffers.cpp
        src/implementation/linear.cpp
        src/implementation/parser.cpp
)