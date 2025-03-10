cmake_minimum_required(VERSION 3.11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

file(GLOB srcFiles "${CMAKE_SOURCE_DIR}/tests/*.c")

foreach(fileDir ${srcFiles})
get_filename_component(fileName ${fileDir} NAME_WE)
project(${fileName})

add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/tests/${fileName}.c" )

target_link_libraries(${PROJECT_NAME} unity)

target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendor/Unity/src")

endforeach()

