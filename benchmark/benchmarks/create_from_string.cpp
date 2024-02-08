#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void CreateFromString(benchmark::State& state) {
    std::string str(state.range(0), '1');
    for (auto _ : state) {
        bignum::BigNumber number(str);
    }
}
BENCHMARK(CreateFromString)->Range(1, 1 << 20);