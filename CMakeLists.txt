#TODO : document
# For some reason, CMAKE will only output compiler warnings when a clean rebuild is done
# DO CLEAN REBUILD FOR WARNINGS!!!
cmake_minimum_required(VERSION 3.11)
set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

project(GPTracer)

add_compile_options(/W4 /fsanitize=address)

execute_process(COMMAND git submodule update --init --recursive)

add_executable(${PROJECT_NAME} "src/GPTracer.c" "src/datatypes/Tuple.c" "src/datatypes/Canvas.c" "src/PPM.c" "src/datatypes/Mat.c" "src/CommonOperations.c" "src/datatypes/Ray.c" "src/datatypes/Sphere.c" "src/datatypes/Intersection.c" "src/datatypes/Material.c" "src/datatypes/Pointlight.c")

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendor/Unity/src")

add_subdirectory("vendor/Unity")
add_subdirectory("tests")
target_link_libraries(${PROJECT_NAME} unity)

