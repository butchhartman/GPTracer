

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
cmake_minimum_required(VERSION 3.11)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

project(GPTracer)

execute_process(COMMAND git submodule update --init --recursive)

add_executable(${PROJECT_NAME} "src/GPTracer.c")

add_subdirectory("vendor/Unity")

target_link_libraries(${PROJECT_NAME} unity)


target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendor/Unity/src")


add_subdirectory("tests")