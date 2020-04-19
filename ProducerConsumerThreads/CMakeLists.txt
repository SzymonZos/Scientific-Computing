project(ProducerConsumerThreads)

set(TOOLCHAIN_BUILD "${CMAKE_CXX_COMPILER_ID}${CMAKE_BUILD_TYPE}")

add_executable(ProducerConsumerThreads main.cpp)

target_compile_definitions(ProducerConsumerThreads PRIVATE
    BUILD_INFO="${CMAKE_SYSTEM_NAME} ${TOOLCHAIN_BUILD}"
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

message(${PROJECT_SOURCE_DIR})

set_target_properties(ProducerConsumerThreads
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(ProducerConsumerThreads PRIVATE
    include
)
