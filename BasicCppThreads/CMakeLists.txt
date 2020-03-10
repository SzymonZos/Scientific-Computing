cmake_minimum_required(VERSION 3.15)
project(BasicCppThreads)

set(CMAKE_CXX_STANDARD 17)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
endif()

add_executable(BasicCppThreads main.cpp Timer.cpp)

