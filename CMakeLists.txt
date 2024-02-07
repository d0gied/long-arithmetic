# library name: LongArithmetic
# author: German Novokhodskii
# date: 2024
# description: library for long arithmetic

cmake_minimum_required(VERSION 3.10)
project(long_arithmetic)

set(CMAKE_CXX_STANDARD 17)

# Добавьте поддиректорию для вашего модуля LongArithmetic
add_subdirectory(long_arithmetic)

# Add benchmarking
add_subdirectory(benchmark)


# Добавьте поддиректорию для ваших тестов
enable_testing()
add_subdirectory(tests)
