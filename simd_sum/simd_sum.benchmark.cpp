#include <benchmark/benchmark.h>
#include <blaze/Blaze.h>

#include <iostream>

constexpr int kArrSize = 20;

static void BM_LoopSum20Double(benchmark::State& state) {
    std::vector<double> arr(kArrSize);
    for (int i = 0; i < kArrSize; ++i) {
        arr[i] = i * 2.0;
    }

    double sum = 0;
    for (auto _ : state) {
        sum = 0;
        for (int i = 0; i < kArrSize; ++i) {
            sum += arr[i];
        }
        benchmark::DoNotOptimize(sum);
    }
    std::cout << sum << std::endl;
}

static void BM_DotProductSum20Double(benchmark::State& state) {
    blaze::StaticVector<double, kArrSize> arr;
    blaze::StaticVector<double, kArrSize> one_arr;
    for (int i = 0; i < kArrSize; ++i) {
        one_arr[i] = 1;
        arr[i] = i * 2.0;
    }

    double sum = 0;
    for (auto _ : state) {
        sum = blaze::trans(one_arr) * arr;
        benchmark::DoNotOptimize(sum);
    }
    std::cout << sum << std::endl;
}

// Register the function as a benchmark
BENCHMARK(BM_LoopSum20Double);
BENCHMARK(BM_DotProductSum20Double);

// Run the benchmark