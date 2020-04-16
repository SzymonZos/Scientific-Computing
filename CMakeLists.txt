cmake_minimum_required(VERSION 3.15)
project(ScientificComputing)

set(CMAKE_CXX_STANDARD 17)

set(TIMER_DIR external/Timer)

add_compile_options(
    -Werror
    -Wall
    -Wextra
    -Wshadow # Warn if variable overshadows parent context
    -Wnon-virtual-dtor # Warn if class with virtual func has no virtual dtor
    -Wcast-align # Warn for potential performance problem casts
    -Wunused # Warn on anything being unused
    -Woverloaded-virtual # Warn if overload a virtual function
    -Wpedantic # Warn if non-standard C++ is used
    -Wconversion # Warn on type conversions that may lose data
    -Wsign-conversion # Warn on sign conversions
    -Wdouble-promotion # Warn if float is implicit promoted to double
    -Wold-style-cast # Warn if c style cast is performed
    -fconstexpr-depth=1024
)

if(CMAKE_SYSTEM_NAME STREQUAL "Linux")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        add_compile_options(
            -g
            -rdynamic
        )
    endif()
    add_link_options(
        -pthread
    )
endif()

include_directories(SYSTEM
    ${TIMER_DIR}
)

add_subdirectory(BasicCppThreads)
add_subdirectory(ProducerConsumerThreads)