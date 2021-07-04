#include <benchmark/benchmark.h>
#define BLAZE_USE_SLEEF 1
#include <blaze/Blaze.h>
#include <iostream>

//void prefix_sum(double* a, int n) {
//  for (int i = 0; i < n - 1; ++i) {
//    a[i+1] += a[i];
//  }
//}
//
//void better_prefix_sum(double* a, int n) {
//  auto tmp = a[0];
//  for (int i = 1; i < n; ++i) {
//    tmp += a[i];
//    a[i] = tmp;
//  }
//}
//
//static void BM_prefix_sum(benchmark::State& state) {
//  double a[8];
//  for (int i = 0; i < 8; ++i) {
//    a[i] = i;
//  }
//
//  for (auto _ : state) {
//    prefix_sum(a, 8);
//    benchmark::DoNotOptimize(a);
//  }
//}
//
//static void BM_better_prefix_sum(benchmark::State& state) {
//  double a[8];
//  for (int i = 0; i < 8; ++i) {
//    a[i] = i;
//  }
//
//  for (auto _ : state) {
//    better_prefix_sum(a, 8);
//    benchmark::DoNotOptimize(a);
//  }
//}
//
//BENCHMARK(BM_prefix_sum);
//BENCHMARK(BM_better_prefix_sum);
//
//double haha(double i) {
//  blaze::StaticVector<double, 5UL> temp;
//  temp += i;
//  temp *= i;
//  return blaze::sum(temp);
//}
//
//double haha2(double i) {
//  blaze::StaticVector<double, 5UL> temp;
//  blaze::subvector(temp, 0, 4UL) += i;
//  blaze::subvector(temp, 0, 4UL) *= i;
//  temp[4] += i;
//  temp[4] *= i;
//  return blaze::sum(temp);
//}
//
//double haha3(double i) {
//  blaze::StaticVector<double, 4UL> temp;
//  temp += i;
//  temp *= i;
//  return blaze::sum(temp);
//}
//
//static void BM_haha(benchmark::State& state) {
//  for (auto _ : state) {
//    benchmark::DoNotOptimize(haha((double)state.range(0)));
//  }
//}
//
//static void BM_haha2(benchmark::State& state) {
//  for (auto _ : state) {
//    benchmark::DoNotOptimize(haha2((double)state.range(0)));
//  }
//}
//
//static void BM_haha3(benchmark::State& state) {
//  for (auto _ : state) {
//    benchmark::DoNotOptimize(haha3((double)state.range(0)));
//  }
//}
//
//
//BENCHMARK(BM_haha)->Arg(23423);
//BENCHMARK(BM_haha2)->Arg(23423);
//BENCHMARK(BM_haha3)->Arg(23423);
//

double hehe(double i) {
  blaze::StaticVector<double, 5UL> temp;
  temp += i;
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  return temp[0];
}

double hehe2(double i) {
  blaze::StaticVector<double, 5UL> temp;
  blaze::subvector(temp, 0, 4UL) += i;
  temp[4] += i;
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  blaze::subvector(temp, 0, 4UL) = blaze::log(blaze::subvector(temp, 0, 4UL));
  temp[4] = blaze::log(temp[4]);
  return temp[0];
}

double hehe3(double i) {
  blaze::StaticVector<double, 4UL> temp;
  temp += i;
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  temp = blaze::log(temp);
  return temp[0];
}

static void BM_hehe(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(hehe((double)state.range(0)));
  }
}

static void BM_hehe2(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(hehe2((double)state.range(0)));
  }
}

static void BM_hehe3(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(hehe3((double)state.range(0)));
  }
}

#if defined(__FMA__)
#define FGF
#else
#define SDFSD
#endif

BENCHMARK(BM_hehe)->Arg(23423);
//BENCHMARK(BM_hehe2)->Arg(23423);
//BENCHMARK(BM_hehe3)->Arg(23423);