cmake_minimum_required(VERSION 3.11)
# with this current configuration, there can only be one source file per test file
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests")

file(GLOB srcFiles "${CMAKE_SOURCE_DIR}/tests/*.c")
file(GLOB testCSourceFiles "${CMAKE_SOURCE_DIR}/src/datatypes/*.c")

foreach(fileDir ${srcFiles})

	get_filename_component(fileName ${fileDir} NAME_WE)
	string(REPLACE "test_" "" sourceFileName ${fileName})
	project(${fileName})


	add_executable(${PROJECT_NAME} "${CMAKE_SOURCE_DIR}/tests/${fileName}.c" ${testCSourceFiles} "${CMAKE_SOURCE_DIR}/src/CommonOperations.c") #{CMAKE_SOURCE_DIR}/src/${sourceFileName}.c")

	target_link_libraries(${PROJECT_NAME} unity)
	
	target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/include")
	target_include_directories(${PROJECT_NAME} SYSTEM PUBLIC "${CMAKE_SOURCE_DIR}/vendor/Unity/src")

	add_test(${fileName} ${PROJECT_NAME})
endforeach()

