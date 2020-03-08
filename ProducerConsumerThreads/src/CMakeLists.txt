include_directories(${PROJECT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES dataflow/*)

add_library(src ${SRC_FILES})