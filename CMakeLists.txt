cmake_minimum_required(VERSION 3.30)
project(aoc24_cpp)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -Weffc++ -pedantic)

add_executable(aoc24_cpp src/main.cpp)
