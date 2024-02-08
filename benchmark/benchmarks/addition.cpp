#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void AdditionLongToLong(benchmark::State& state) {
    bignum::BigNumber number1(std::string(state.range(0), '9'));
    bignum::BigNumber number2(std::string(state.range(0), '9'));
    for (auto _ : state) {
        number1 + number2;
    }
}
BENCHMARK(AdditionLongToLong)->Range(1, 1 << 20);