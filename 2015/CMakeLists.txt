project(Year2015Tests LANGUAGES CXX)

file(GLOB sources CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/*.cpp
)

file(GLOB inputs CONFIGURE_DEPENDS 
    ${PROJECT_SOURCE_DIR}/Day*.txt
)

add_executable(${PROJECT_NAME} ${sources} ${inputs})
target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
target_link_libraries(${PROJECT_NAME} aoc gtest)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy ${inputs} $<TARGET_FILE_DIR:${PROJECT_NAME}>
)

enable_testing()
add_test(${PROJECT_NAME} ${PROJECT_NAME})
