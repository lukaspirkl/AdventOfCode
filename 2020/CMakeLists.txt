project(Year2020Tests LANGUAGES CXX)

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
    Day10.cpp
    Day11.cpp
    Day12.cpp
)

set(inputs
    Day01.txt
    Day02.txt
    Day03.txt
    Day04.txt
    Day05.txt
    Day06.txt
    Day07.txt
    Day08.txt
    Day09.txt
    Day10.txt
    Day11.txt
    Day12.txt
)

list(TRANSFORM inputs PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

add_executable(${PROJECT_NAME} ${sources})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} aoc gtest)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
