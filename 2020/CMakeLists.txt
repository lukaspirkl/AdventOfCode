
find_package(gtest REQUIRED)

set(sources
    pch.h
    Day01.cpp
)

set(inputs
    Day01.txt
)

list(TRANSFORM inputs PREPEND "${CMAKE_CURRENT_LIST_DIR}/")

add_executable(Year2020 ${sources} ${inputs})
target_precompile_headers(Year2020 PRIVATE pch.h)
target_compile_features(Year2020 PRIVATE cxx_std_17)
target_link_libraries(Year2020 aoc gtest::gtest)

add_custom_command(TARGET Year2020 POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:Year2020>
)

enable_testing()
add_test(Year2020 Year2020)
