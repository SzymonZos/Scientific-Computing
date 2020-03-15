cmake_minimum_required(VERSION 3.15)
project(ProducerConsumerThreads)

set(CMAKE_CXX_STANDARD 17)
set(ENTRY_POINT main.cpp)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread -g -rdynamic")
endif()

include_directories(include)

add_executable(ProducerConsumerThreads ${ENTRY_POINT})
