#include <benchmark/benchmark.h>

#include <charconv>

volatile char int_str[] = "5234513";
volatile char float_str[] = "754.234";

static void BM_Atof(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(std::atof(const_cast<const char *>(float_str)));
  }
}

static void BM_Stof(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(std::stof(const_cast<const char *>(float_str)));
  }
}

static void BM_FromCharsInt(benchmark::State &state) {
  int result;
  for (auto _ : state) {
    std::from_chars(const_cast<const char *>(int_str) + 0, const_cast<const char *>(int_str) + 8, result);
  }
  benchmark::DoNotOptimize(result);
}

static void BM_Atoi(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(std::atoi(const_cast<const char *>(int_str)));
  }
}

static void BM_Stoi(benchmark::State &state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(std::stoi(const_cast<const char *>(int_str)));
  }
}

// Register the function as a benchmark
BENCHMARK(BM_Atof);
BENCHMARK(BM_Stof);
BENCHMARK(BM_FromCharsInt);
BENCHMARK(BM_Atoi);
BENCHMARK(BM_Stoi);