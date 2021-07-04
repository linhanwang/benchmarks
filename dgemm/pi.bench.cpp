#include <benchmark/benchmark.h>
#include <immintrin.h>

#include <cstdint>

double compute_pi_naive(std::size_t dt) {
  double pi = 0.0;
  double delta = 1.0 / dt;
  for (std::size_t i = 0; i < dt; ++i) {
    double x = (double)i / dt;
    pi += delta / (1.0 + x * x);
  }
  return pi * 4.0;
}

float cpuPI(int num) {
  float sum = 0.0f;
  float temp;

  for (int i = 0; i < num; i++) {
    temp = (i + 0.5f) / num;
    sum += 4 / (1 + temp*temp);
  }

  return sum / num;
}

double compute_pi_omp_avx(std::size_t dt) {
  double pi = 0.0;
  double delta = 1.0 / dt;
  __m256d ymm0, ymm1, ymm2, ymm3, ymm4;
  ymm0 = _mm256_set1_pd(1.0);
  ymm1 = _mm256_set1_pd(delta);
  ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta, 0.0);
  ymm4 = _mm256_setzero_pd();

  for (int i = 0; i <= dt - 4; i += 4) {
    ymm3 = _mm256_set1_pd(i * delta);
    ymm3 = _mm256_add_pd(ymm3, ymm2);
    ymm3 = _mm256_mul_pd(ymm3, ymm3);
    ymm3 = _mm256_add_pd(ymm0, ymm3);
    ymm3 = _mm256_div_pd(ymm1, ymm3);
    ymm4 = _mm256_add_pd(ymm4, ymm3);
  }

  double tmp[4] __attribute__((aligned(32)));
  _mm256_store_pd(tmp, ymm4);
  pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

  return pi * 4.0;
}

double compute_pi_omp_avx_optimized(std::size_t dt) {
  double pi = 0.0;
  double delta = 1.0 / dt;
  __m256d ymm0, ymm1, ymm2, ymm3, ymm4, ymm5, ymm6;
  ymm0 = _mm256_set1_pd(1.0);
  ymm1 = _mm256_set1_pd(delta);
  ymm2 = _mm256_set_pd(delta * 3, delta * 2, delta, 0.0);
  ymm4 = _mm256_setzero_pd();

  ymm5 = _mm256_setzero_pd();
  for (int i = 0; i <= dt - 8; i += 8) {
    ymm3 = _mm256_set1_pd(i * delta);
    ymm3 = _mm256_add_pd(ymm3, ymm2);
    ymm3 = _mm256_mul_pd(ymm3, ymm3);
    ymm3 = _mm256_add_pd(ymm0, ymm3);
    ymm3 = _mm256_div_pd(ymm1, ymm3);
    ymm4 = _mm256_add_pd(ymm4, ymm3);

    ymm6 = _mm256_set1_pd((i + 4) * delta);
    ymm6 = _mm256_add_pd(ymm6, ymm2);
    ymm6 = _mm256_mul_pd(ymm6, ymm6);
    ymm6 = _mm256_add_pd(ymm0, ymm6);
    ymm6 = _mm256_div_pd(ymm1, ymm6);
    ymm5 = _mm256_add_pd(ymm5, ymm6);
  }
  ymm4 = _mm256_add_pd(ymm5, ymm6);

  double tmp[4] __attribute__((aligned(32)));
  _mm256_store_pd(tmp, ymm4);
  pi += tmp[0] + tmp[1] + tmp[2] + tmp[3];

  return pi * 4.0;
}

static void BM_compute_pi_naive(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(compute_pi_naive(state.range(0)));
  }
}

static void BM_cpuPI(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(cpuPI(state.range(0)));
  }
}

static void BM_compute_pi_omp_avx(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(compute_pi_omp_avx(state.range(0)));
  }
}

static void BM_compute_pi_omp_avx_optimized(benchmark::State& state) {
  for (auto _ : state) {
    benchmark::DoNotOptimize(compute_pi_omp_avx_optimized(state.range(0)));
  }
}

BENCHMARK(BM_compute_pi_naive)->Arg(1 << 8);
BENCHMARK(BM_cpuPI)->Arg(1 << 8);
BENCHMARK(BM_compute_pi_omp_avx)->Arg(1 << 8);
BENCHMARK(BM_compute_pi_omp_avx_optimized)->Arg(1 << 8);
