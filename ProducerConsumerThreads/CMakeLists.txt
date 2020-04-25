project(ProducerConsumerThreads)

add_executable(ProducerConsumerThreads main.cpp)

target_compile_definitions(ProducerConsumerThreads PRIVATE
    BUILD_INFO="${CMAKE_SYSTEM_NAME} ${TOOLCHAIN_BUILD}"
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

set_target_properties(ProducerConsumerThreads
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(ProducerConsumerThreads PRIVATE
    include
)
