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

set(CMAKE_CXX_FLAGS_DEBUG "-Wall -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -Wall -DNDEBUG")

message(STATUS "CMAKE_CXX_FLAGS_DEBUG: ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "CMAKE_CXX_FLAGS_RELEASE: ${CMAKE_CXX_FLAGS_RELEASE}")

message(STATUS "CURRENT ENVIRONMENT: ${CMAKE_BUILD_TYPE}")