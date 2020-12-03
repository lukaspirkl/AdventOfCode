project(aoc LANGUAGES CXX)

set(sources
    src/aoc.cpp
    src/intcode.cpp
)

add_library(${PROJECT_NAME} STATIC ${sources})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
