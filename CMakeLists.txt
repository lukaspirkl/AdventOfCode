cmake_minimum_required(VERSION 3.16)

project(AdventOfCode LANGUAGES C CXX)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/googletest)
add_subdirectory(aoc)
add_subdirectory(2015)
add_subdirectory(2019/Solutions)
add_subdirectory(2019/Cryostasis)
add_subdirectory(2020)
