#include <benchmark/benchmark.h>
#include <unistd.h>

#include "utils.h"

static void BM_CLOCK_TIME(benchmark::State& state) {
  int64_t time{0};
  for (auto _ : state) {
    time = NowNs();
    benchmark::DoNotOptimize(time);
  }
}

static void BM_TSC_TIME(benchmark::State& state) {
  int64_t time{0};
  for (auto _ : state) {
    time = NowTscNs();
    benchmark::DoNotOptimize(time);
  }
}

static void BM_GET_PID(benchmark::State& state) {
  decltype(getpid()) pid{0};
  for (auto _ : state) {
    pid = getpid();
    benchmark::DoNotOptimize(pid);
  }
}

static void BM_GET_CPU(benchmark::State& state) {
  unsigned int numa, node;
  for (auto _ : state) {
    auto ret = getcpu(&numa, &node);
    benchmark::DoNotOptimize(ret);
    benchmark::DoNotOptimize(numa);
    benchmark::DoNotOptimize(node);
  }
}

// Register the function as a benchmark
//BENCHMARK(BM_CLOCK_TIME);
//BENCHMARK(BM_TSC_TIME);
//BENCHMARK(BM_GET_PID);
//BENCHMARK(BM_GET_CPU);

struct C {
  static const std::string& magic_ref() {
    static std::string s = "linhan";
    return s;
  }

  const std::string& s = magic_ref();

  const std::string& magic_ref_cached() {
    return s;
  }
};

static void BM_static(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(C::magic_ref().size());
  }
}

BENCHMARK(BM_static);

static void BM_non_static(benchmark::State& state) {
  C c{};
  for (auto _ : state) {
    benchmark::DoNotOptimize(c.magic_ref_cached().size());
  }
}

BENCHMARK(BM_non_static);