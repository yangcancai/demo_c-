cmake_minimum_required(VERSION 3.16)
project(test)

set(CMAKE_CXX_STANDARD 14)

add_executable(test main.cpp)
add_executable(debug_dead_lock.cpp debug_dead_lock.cpp)