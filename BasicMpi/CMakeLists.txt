project(BasicMpi)

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS "src/*.cpp")
add_executable(BasicMpi ${SRC})

target_compile_definitions(BasicMpi PRIVATE
    BUILD_INFO="${CMAKE_SYSTEM_NAME} ${TOOLCHAIN_BUILD}"
    PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
)

set_target_properties(BasicMpi
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)

target_include_directories(BasicMpi PRIVATE
    include
)

target_link_libraries(BasicMpi PRIVATE
    MPI
)
