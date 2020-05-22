project(ProducerConsumerMpi)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "*.cpp")
add_executable(ProducerConsumerMpi ${SRC})

set_target_properties(ProducerConsumerMpi
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(ProducerConsumerMpi PRIVATE
    include
    ${INTERFACES_DIR}
)

target_link_libraries(ProducerConsumerMpi PRIVATE
    MPI
)
