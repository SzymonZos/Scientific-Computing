project(ProducerConsumerMpi)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "*.cpp")
add_executable(ProducerConsumerMpi ${SRC})

target_compile_definitions(ProducerConsumerMpi PRIVATE
    BUILD_INFO="${CMAKE_SYSTEM_NAME} ${TOOLCHAIN_BUILD}"
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

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
