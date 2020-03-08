cmake_minimum_required(VERSION 3.15)
project(ProducerConsumerThreads)

set(CMAKE_CXX_STANDARD 17)
set(ENTRY_POINT main.cpp)

include_directories(include)
add_subdirectory(src)

add_executable(ProducerConsumerThreads ${ENTRY_POINT})
target_link_libraries(ProducerConsumerThreads src)