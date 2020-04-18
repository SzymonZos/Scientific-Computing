project(ProducerConsumerThreads)

add_executable(ProducerConsumerThreads main.cpp)

set_target_properties(ProducerConsumerThreads
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin"
    )

target_include_directories(ProducerConsumerThreads PRIVATE
    include
)