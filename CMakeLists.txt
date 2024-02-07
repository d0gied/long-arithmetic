# library name: LongArithmetic
# author: German Novokhodskii
# date: 2024
# description: library for long arithmetic

cmake_minimum_required(VERSION 3.10)
project(long_arithmetic)

set(CMAKE_CXX_STANDARD 17)

# Добавьте Google Test как поддиректорию
add_subdirectory(googletest)

# Включите заголовочные файлы Google Test
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

# Соберите все исходные файлы из папки src
file(GLOB SOURCES "src/*.cpp")

# Создайте общую библиотеку
add_library(long_arithmetic SHARED ${SOURCES})

# Добавьте папку include в пути поиска заголовочных файлов
target_include_directories(long_arithmetic PUBLIC include)

enable_testing() #to  discover tests in test explorer

# Свяжите библиотеку с Google Test
target_link_libraries(long_arithmetic gtest gtest_main)

# Создайте исполняемый файл для тестов
add_executable(run_tests tests/constructor.cpp)

# Свяжите исполняемый файл тестов с вашей библиотекой и Google Test
target_link_libraries(run_tests long_arithmetic gtest gtest_main)

include(GoogleTest)
gtest_discover_tests(run_tests) # discovers tests by asking the compiled test executable to enumerate its tests
