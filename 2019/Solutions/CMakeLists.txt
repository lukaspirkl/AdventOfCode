project(Year2019Tests LANGUAGES CXX)

set(sources
    Main.cpp
    Day01.cpp
    Day02.cpp
    Day03.cpp
    Day04.cpp
    Day05.cpp
    Day06.cpp
    Day07.cpp
    Day08.cpp
    Day09.cpp
    Day11.cpp
    Day12.cpp
    Day13.cpp
    Day14.cpp
    Day15.cpp
    Day16.cpp
    Day17.cpp
    Day18.cpp
    Day19.cpp
    Day20.cpp
    Day21.cpp
    Day22.cpp
    Day23.cpp
    Day24.cpp
    Day25.cpp
)

set(inputs
    Day01.txt
    Day03.txt
    Day06.txt
    Day08.txt
    Day09.txt
    Day11.txt
    Day13.txt
    Day14.txt
    Day15.txt
    Day16.txt
    Day17.txt
    Day18.txt
    Day19.txt
    Day20.txt
    Day21.txt
    Day22.txt
    Day23.txt
    Day25.txt
)

list(TRANSFORM inputs PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

add_executable(${PROJECT_NAME} ${sources} ${inputs})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} aoc gtest gmock)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../../vendor/boost)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
