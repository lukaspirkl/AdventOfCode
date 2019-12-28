set(sources
    src/aoc.cpp
    src/intcode.cpp
    include/aoc.h
    include/intcode.h
)

add_library(aoc STATIC ${sources})
target_include_directories(aoc PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
