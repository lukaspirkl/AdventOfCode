
find_package(gtest REQUIRED)

set(sources
    pch.h
    md5.h
    md5.cpp
    Day01.cpp
    Day02.cpp
    Day03.cpp
    Day04.cpp
    Day05.cpp
)

set(inputs
    Day02.txt
    Day03.txt
    Day05.txt
)

list(TRANSFORM inputs PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

add_executable(Year2015 ${sources})
target_precompile_headers(Year2015 PRIVATE pch.h)
target_compile_features(Year2015 PRIVATE cxx_std_17)
target_link_libraries(Year2015 aoc gtest::gtest)

add_custom_command(TARGET Year2015 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:Year2015>
)

enable_testing()
add_test(Year2015 Year2015)
