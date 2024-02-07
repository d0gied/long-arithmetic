#include <benchmark/benchmark.h>
#include <long_arithmetic.h>

static void CompareOneToLong(benchmark::State& state) {
    bignum::BigNumber a("1");
    bignum::BigNumber b(state.range(0), '2');

    for (auto _ : state) {
        benchmark::DoNotOptimize(a < b);
    }
}

static void CompareLongToOne(benchmark::State& state) {
    bignum::BigNumber a(state.range(0), '2');
    bignum::BigNumber b("1");

    for (auto _ : state) {
        benchmark::DoNotOptimize(a < b);
    }
}

static void CompareLongToLong(benchmark::State& state) {
    bignum::BigNumber a(state.range(0), '1');
    bignum::BigNumber b(state.range(0), '2');

    for (auto _ : state) {
        benchmark::DoNotOptimize(a < b);
    }
}

BENCHMARK(CompareOneToLong)->Range(1, 1 << 20);
BENCHMARK(CompareLongToOne)->Range(1, 1 << 20);
BENCHMARK(CompareLongToLong)->Range(1, 1 << 20);