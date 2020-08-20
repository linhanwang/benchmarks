#include <benchmark/benchmark.h>
#include "utils.h"

static void BM_CLOCK_TIME(benchmark::State& state) {
    int64_t time{0};
    for (auto _ : state) {
        time = NowNs();
    }
}

static void BM_TSC_TIME(benchmark::State& state) {
    int64_t time{0};
    for (auto _ : state) {
        time = get_timestamp();
    }
}

// Register the function as a benchmark
BENCHMARK(BM_CLOCK_TIME);
BENCHMARK(BM_TSC_TIME);

// Run the benchmark
BENCHMARK_MAIN();