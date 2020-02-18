cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

project(fn-proj)

# Add source to this project's executable.

add_executable (find-number "main.cpp" "students/example.cpp") 
