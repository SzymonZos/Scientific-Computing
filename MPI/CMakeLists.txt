cmake_minimum_required(VERSION 3.15)
project(MPI VERSION 0.1.0 DESCRIPTION "MPICH 3.3 c++ wrapper")

set(CMAKE_CXX_STANDARD 20)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp")
add_library(MPI STATIC ${SRC})

target_compile_options(MPI PRIVATE
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

set_target_properties(MPI PROPERTIES
    PUBLIC_HEADER include/Mpi.hpp
)

target_include_directories(MPI PRIVATE
    include
)
