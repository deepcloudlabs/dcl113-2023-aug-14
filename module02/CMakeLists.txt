cmake_minimum_required(VERSION 3.26)
project(module02)

set(CMAKE_CXX_STANDARD 20)

add_executable(module02 main.cpp
        person.cpp
        person.h)
