# library name: LongArithmetic
# author: German Novokhodskii
# date: 2024
# description: library for long arithmetic

# add source files
file (GLOB_RECURSE SOURCES "src/*.cpp")
add_library(long_arithmetic SHARED ${SOURCES})

target_include_directories(long_arithmetic PUBLIC include)