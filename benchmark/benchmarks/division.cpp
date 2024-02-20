#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void Divide(benchmark::State& state) {
    bignum::BigNumber number1("1");
    bignum::BigNumber number2("3");
    bignum::SET_DIV_PRECISION(state.range(0));
    for (auto _ : state) {
        (number1 / number2);
    }
}
BENCHMARK(Divide)->Range(1, 1 << 20);