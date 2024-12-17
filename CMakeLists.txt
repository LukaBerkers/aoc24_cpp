cmake_minimum_required(VERSION 3.30)
project(aoc24_cpp)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wconversion -Wsign-conversion -pedantic)

include(FetchContent)
FetchContent_Declare(
        lexy URL https://github.com/foonathan/lexy/releases/download/v2022.12.1/lexy-src.zip
)
FetchContent_MakeAvailable(lexy)

find_package(spdlog REQUIRED)

add_executable(aoc24_cpp
        src/main.cpp
        src/utils.h
        src/AocException.h
        src/day1/day1.cpp
        src/day1/day1.h
        src/day2/Report.h
        src/day2/day2.cpp
        src/day2/day2.h
)

target_link_libraries(aoc24_cpp PRIVATE lexy spdlog::spdlog)
