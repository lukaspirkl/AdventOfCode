
find_package(gtest REQUIRED)

set(sources
    pch.h
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

add_executable(Year2019 ${sources} ${inputs})
target_precompile_headers(Year2019 PRIVATE pch.h)
target_compile_features(Year2019 PRIVATE cxx_std_17)
target_link_libraries(Year2019 aoc gtest::gtest)

list(TRANSFORM inputs PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

add_custom_command(TARGET Year2019 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:Year2019>
)

enable_testing()
add_test(Year2019 Year2019)
