#include <benchmark/benchmark.h>
#define BLAZE_USE_SLEEF 1
#include <blaze/Blaze.h>
#include <sleef.h>
#include <iostream>

static void BM_std_log(benchmark::State& state) {
//  std::cout << std::log(12345.6) << std::endl;
//  std::cout << blaze::log(12345.6) << std::endl;
//  std::cout << Sleef_log_u35(12345.6) << std::endl;

  std::vector<double> vec(state.range(0), 12345.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(std::log(v));
    }
  }
}

static void BM_blaze_log(benchmark::State& state) {
  std::vector<double> vec(state.range(0), 12345.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(blaze::log(v));
    }
  }
}

static void BM_sleef_log(benchmark::State& state) {
  std::vector<double> vec(state.range(0), 12345.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(Sleef_log_u35(v));
    }
  }
}

static void BM_std_exp(benchmark::State& state) {
//  std::cout << std::exp(5.6) << std::endl;
//  std::cout << blaze::exp(5.6) << std::endl;
//  std::cout << Sleef_exp_u10(5.6) << std::endl;

  std::vector<double> vec(state.range(0), 5.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(std::exp(v));
    }
  }
}

static void BM_blaze_exp(benchmark::State& state) {
  std::vector<double> vec(state.range(0), 5.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(blaze::exp(v));
    }
  }
}

static void BM_sleef_exp(benchmark::State& state) {
  std::vector<double> vec(state.range(0), 5.6);
  for (auto _ : state) {
    for (auto v : vec) {
      benchmark::DoNotOptimize(Sleef_exp_u10(v));
    }
  }
}

static void BM_std_log_vec(benchmark::State& state) {
//  std::cout << std::log(12345.6) << std::endl;
//  std::cout << blaze::log(12345.6) << std::endl;
//  std::cout << Sleef_log_u35(12345.6) << std::endl;

  std::vector<double> vec(32, 12345.6);
  std::vector<double> vec2(32, 12345.6);
  for (auto _ : state) {
    for (int i = 0; i < 32; ++i) {
      vec2[i] = std::log(vec[i]);
    }
    benchmark::DoNotOptimize(vec2.data());
    benchmark::ClobberMemory();
  }
}

static void BM_blaze_log_vec(benchmark::State& state) {
  blaze::StaticVector<double, 32UL> a, b;
  a += 12345.6;
  for (auto _ : state) {
    b = blaze::log(a);
    benchmark::DoNotOptimize(b);
    benchmark::ClobberMemory();
  }
}


//BENCHMARK(BM_std_log)->Arg(32);
//BENCHMARK(BM_blaze_log)->Arg(32);
//BENCHMARK(BM_sleef_log)->Arg(32);
//
//BENCHMARK(BM_std_exp)->Arg(32);
//BENCHMARK(BM_blaze_exp)->Arg(32);
//BENCHMARK(BM_sleef_exp)->Arg(32);

BENCHMARK(BM_std_log_vec);
BENCHMARK(BM_blaze_log_vec);