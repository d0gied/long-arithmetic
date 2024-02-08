#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void SubstractionLongToLong(benchmark::State& state) {
    bignum::BigNumber number1(std::string(state.range(0), '1'));
    bignum::BigNumber number2(std::string(state.range(0), '9'));
    for (auto _ : state) {
        number1 - number2;
    }
}

BENCHMARK(SubstractionLongToLong)->Range(1, 1 << 20);