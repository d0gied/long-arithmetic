#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void CompareLongToLong(benchmark::State& state) {
    bignum::BigNumber a(std::string(state.range(0), '1'));
    bignum::BigNumber b(std::string(state.range(0), '2'));

    for (auto _ : state) {
        benchmark::DoNotOptimize(a < b);
    }
}

// BENCHMARK(CompareOneToLong)->Range(1, 1 << 20);
// BENCHMARK(CompareLongToOne)->Range(1, 1 << 20);
// BENCHMARK(CompareLongToLong)->Range(1, 1 << 20);