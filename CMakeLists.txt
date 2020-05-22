cmake_minimum_required(VERSION 3.15)
project(ScientificComputing)

set(CMAKE_CXX_STANDARD 20)

set(SPDLOG_DIR ${PROJECT_SOURCE_DIR}/external/spdlog)
set(TIMER_DIR ${PROJECT_SOURCE_DIR}/external/Timer)
set(OPERATORS_DIR ${PROJECT_SOURCE_DIR}/external/Generic-Ostream-Operators)
set(GSL_DIR ${PROJECT_SOURCE_DIR}/external/GSL)
set(MPI_DIR ${PROJECT_SOURCE_DIR}/MPI)

set(TOOLCHAIN_BUILD "${CMAKE_CXX_COMPILER_ID}${CMAKE_BUILD_TYPE}")

add_compile_options(
#    -Werror
    -Wall
    -Wextra
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has no virtual dtor
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Wno-overloaded-virtual # Don't warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
    -Wold-style-cast # Warn if c style cast is performed
    -fconstexpr-depth=1024
)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    add_compile_options(
        -stdlib=libc++
    )
    add_link_options(
        -stdlib=libc++
        -lc++abi
    )
endif()

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    add_link_options(
        -pthread
    )
endif()

include_directories(SYSTEM
    ${SPDLOG_DIR}/include
    ${TIMER_DIR}
    ${OPERATORS_DIR}
    ${GSL_DIR}/include
    ${MPI_DIR}/include
)

add_subdirectory(${SPDLOG_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${SPDLOG_DIR})
add_subdirectory(${GSL_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${GSL_DIR})
add_subdirectory(MPI)

add_subdirectory(BasicCppThreads)
add_subdirectory(BasicMpi)
add_subdirectory(ProducerConsumer)
