# Tests module for Long Arithmetic
# author: German Novokhodskii
# date: 2024
# description: library for long arithmetic

# add gtest library
add_subdirectory(extern/googletest)

include(GoogleTest)

# add tests
file(GLOB_RECURSE TESTS_SRC_FILES ./tests/*.cpp)
add_executable(run_tests ${TESTS_SRC_FILES})
target_link_libraries(run_tests gtest gtest_main long_arithmetic)
include_directories(include)


enable_testing()
gtest_discover_tests(run_tests)