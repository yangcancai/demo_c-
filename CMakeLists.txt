cmake_minimum_required(VERSION 3.16)
project(debug_dead_lock)

set(CMAKE_CXX_STANDARD 14)
#SET(CMAKE_CXX_FLAGS_DEBUG "-lpthread")
add_executable(debug_dead_lock debug_dead_lock.cpp)
target_link_libraries(debug_dead_lock 
pthread)
