#include <benchmark/benchmark.h>

#include <immintrin.h>

void dgemm(int n, double* A, double* B, double* C) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      double cij = C[i + j * n];
      for (int k = 0; k < n; ++k) {
        cij += A[i + k * n] * B[k + j * n];  // cij += A[i][k]
      }
      C[i + j * n] = cij;
    }
  }
}

void dgemm_avx_unaligned(int n, double* A, double* B, double* C) {
  for (int i = 0; i < n; i+=4) {
    for (int j = 0; j < n; ++j) {
      __m256d c0 = _mm256_loadu_pd(C+i+j*n);
      for (int k = 0; k < n; ++k) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B+j*n+k));
        c0 = _mm256_fmadd_pd(_mm256_loadu_pd(A+n*k+i), bb, c0);
      }
      _mm256_storeu_pd(C+i+j*n, c0);
    }
  }
}

void dgemm_avx(int n, double* A, double* B, double* C) {
  for (int i = 0; i < n; i+=4) {
    for (int j = 0; j < n; ++j) {
      __m256d c0 = _mm256_load_pd(C+i+j*n);
      for (int k = 0; k < n; ++k) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B+j*n+k));
        c0 = _mm256_fmadd_pd(_mm256_load_pd(A+n*k+i), bb, c0);
      }
      _mm256_store_pd(C+i+j*n, c0);
    }
  }
}

static void BM_dgemm_avx(benchmark::State& state) {
  std::size_t matrix_size = state.range(0);
  double* a = static_cast<double*>(std::aligned_alloc(32, matrix_size * matrix_size * 8));
  double* b = static_cast<double*>(std::aligned_alloc(32, matrix_size * matrix_size * 8));
  double* c = static_cast<double*>(std::aligned_alloc(32, matrix_size * matrix_size * 8));

  for (auto _ : state) {
    dgemm_avx(matrix_size,a, b, c);
    benchmark::DoNotOptimize(c);
  }
}

static void BM_dgemm_unaligned(benchmark::State& state) {
  std::size_t matrix_size = state.range(0);
  double* a = new double[matrix_size * matrix_size];
  double* b = new double[matrix_size * matrix_size];
  double* c = new double[matrix_size * matrix_size];

  for (auto _ : state) {
    dgemm_avx_unaligned(matrix_size,a, b, c);
    benchmark::DoNotOptimize(c);
  }
}

static void BM_dgemm(benchmark::State& state) {
  std::size_t matrix_size = state.range(0);
  double* a = new double[matrix_size * matrix_size];
  double* b = new double[matrix_size * matrix_size];
  double* c = new double[matrix_size * matrix_size];

  for (auto _ : state) {
    dgemm(matrix_size,a, b, c);
    benchmark::DoNotOptimize(c);
  }
}

BENCHMARK(BM_dgemm)->Arg(8)->Arg(16)->Arg(64);
BENCHMARK(BM_dgemm_unaligned)->Arg(8)->Arg(16)->Arg(64);
BENCHMARK(BM_dgemm_avx)->Arg(8)->Arg(16)->Arg(64);

