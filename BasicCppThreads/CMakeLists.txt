project(BasicCppThreads)

add_executable(BasicCppThreads main.cpp)

set_target_properties(BasicCppThreads
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin/${TOOLCHAIN_BUILD}"
)
