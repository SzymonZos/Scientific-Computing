include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES dataflow/*)
message(STATUS "${SRC_FILES}=${${SRC_FILES}}")

add_library(src ${SRC_FILES})