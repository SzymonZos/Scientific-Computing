cmake_minimum_required(VERSION 3.15)
project(BasicCppThreads)

set(CMAKE_CXX_STANDARD 17)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(BasicCppThreads main.cpp)