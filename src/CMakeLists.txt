aux_source_directory(. SRC_LIST)

include_directories(../include)

find_package(glfw3 REQUIRED)
add_executable(main ${SRC_LIST})
target_link_libraries(main glfw3
							dl
							pthread)
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/build/bin)
