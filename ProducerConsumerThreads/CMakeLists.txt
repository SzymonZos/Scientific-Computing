project(ProducerConsumerThreads)

set(ENTRY_POINT main.cpp)
add_executable(ProducerConsumerThreads ${ENTRY_POINT})

target_include_directories(ProducerConsumerThreads PRIVATE
    include
)
