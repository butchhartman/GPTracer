set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")


project(GPTracer)

execute_process(COMMAND git submodule update --init --recursive)

add_subdirectory("vendor/Unity")

add_executable(${PROJECT_NAME} "src/GPTracer.c" "include/GPTracer.h")

target_link_libraries(${PROJECT_NAME} unity)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendor/Unity/include")