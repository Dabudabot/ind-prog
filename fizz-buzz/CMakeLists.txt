cmake_minimum_required (VERSION 3.8)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/../build)

project(fb-proj)

# Add source to this project's executable.

add_executable (fizz-buzz "main.cpp" "students/example.cpp") 
