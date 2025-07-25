cmake_minimum_required(VERSION 3.28)
project(MeshToASCII)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Release optimization
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -march=native -flto -ffast-math -DNDEBUG")
set(CMAKE_INTERPROCEDURAL_OPTIMIZATION_RELEASE ON)

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