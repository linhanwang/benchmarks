#include <benchmark/benchmark.h>
#include <blaze/Blaze.h>

#include <functional>

constexpr int kArrSize = 20;

static void BM_LoopSum20Double(benchmark::State& state) {
  std::vector<double> arr(kArrSize);
  for (int i = 0; i < kArrSize; ++i) {
    arr[i] = i * 2.0;
  }

  for (auto _ : state) {
    double sum = 0;
    for (int i = 0; i < kArrSize; ++i) {
      sum += arr[i];
    }
    benchmark::DoNotOptimize(sum);
  }
}

static void BM_AccumulateSumDouble(benchmark::State& state) {
  std::vector<double> arr(kArrSize);
  for (int i = 0; i < kArrSize; ++i) {
    arr[i] = i * 2.0;
  }

  for (auto _ : state) {
    benchmark::DoNotOptimize(std::accumulate(arr.begin(), arr.end(), 0));
  }
}

static void BM_DotProductSum20Double(benchmark::State& state) {
  blaze::StaticVector<double, kArrSize> arr;
  for (int i = 0; i < kArrSize; ++i) {
    arr[i] = i * 2.0;
  }

  benchmark::DoNotOptimize(arr);
  for (auto _ : state) {
    benchmark::DoNotOptimize(blaze::sum(arr));
  }
}

// Register the function as a benchmark
BENCHMARK(BM_LoopSum20Double);
BENCHMARK(BM_AccumulateSumDouble);
BENCHMARK(BM_DotProductSum20Double);