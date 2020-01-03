cmake_minimum_required(VERSION 3.16)

project(AdventOfCode LANGUAGES C CXX)

set(CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})

add_subdirectory(aoc)
add_subdirectory(2015)
add_subdirectory(2019/Solutions)
add_subdirectory(2019/Cryostasis)
