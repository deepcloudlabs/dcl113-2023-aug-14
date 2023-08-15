cmake_minimum_required(VERSION 3.26)
project(exercise01)
project(exercise02)
project(exercise03)
project(exercise04)

set(CMAKE_CXX_STANDARD 20)

add_executable(exercise01 exercise01.cpp)
add_executable(exercise02 exercise02.cpp)
add_executable(exercise03 exercise03.cpp person.h person.cpp)
add_executable(exercise04 exercise04.cpp)
