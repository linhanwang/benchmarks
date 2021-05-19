#include <gflags/gflags.h>
#include <immintrin.h>

#include <cstring>
#include <iostream>

void dgemm_unaligned(int n, double* A, double* B, double* C) {
  for (int i = 0; i < n; i += 4) {
    for (int j = 0; j < n; ++j) {
      __m256d c0 = _mm256_loadu_pd(C + i + j * n);
      for (int k = 0; k < n; ++k) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B + j * n + k));
        c0 = _mm256_fmadd_pd(_mm256_loadu_pd(A + n * k + i), bb, c0);
      }
      _mm256_storeu_pd(C + i + j * n, c0);
    }
  }
}

void dgemm(int n, double* A, double* B, double* C) {
  for (int i = 0; i < n; i += 4) {
    for (int j = 0; j < n; ++j) {
      __m256d c0 = _mm256_load_pd(C + i + j * n);
      for (int k = 0; k < n; ++k) {
        __m256d bb = _mm256_broadcastsd_pd(_mm_load_sd(B + j * n + k));
        c0 = _mm256_fmadd_pd(_mm256_load_pd(A + n * k + i), bb, c0);
      }
      _mm256_store_pd(C + i + j * n, c0);
    }
  }
}

void setMatric(int n, double* A) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      *(A + i * n + j) = i * n + j;
    }
  }
}

void printMatrix(int n, double* A) {
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::cout << A[i * n + j] << " ";
    }
    std::cout << "\n";
  }
}

template <std::size_t N>
class Haha;

DEFINE_int32(matrix_size, 4, "");
int main(int argc, char** argv) {
  gflags::ParseCommandLineFlags(&argc, &argv, false);

  __attribute__((aligned(32))) double A[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  __attribute__((aligned(32))) double B[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
  __attribute__((aligned(32))) double C[16];
  std::memset(C, 0, 128);

  //  Haha<sizeof(A)> hehe;
  printMatrix(4, A);
  printMatrix(4, B);
  printMatrix(4, C);

  dgemm(4, A, B, C);

  printMatrix(4, C);

  double* a = static_cast<double*>(std::aligned_alloc(32, FLAGS_matrix_size * FLAGS_matrix_size * 8));
  double* b = static_cast<double*>(std::aligned_alloc(32, FLAGS_matrix_size * FLAGS_matrix_size * 8));
  double* c = static_cast<double*>(std::aligned_alloc(32, FLAGS_matrix_size * FLAGS_matrix_size * 8));

  setMatric(FLAGS_matrix_size, a);
  setMatric(FLAGS_matrix_size, b);
  std::memset(c, 0, FLAGS_matrix_size * FLAGS_matrix_size * 8);
  printMatrix(FLAGS_matrix_size, a);
  printMatrix(FLAGS_matrix_size, b);
  printMatrix(FLAGS_matrix_size, c);

  dgemm(FLAGS_matrix_size, a, b, c);

  printMatrix(FLAGS_matrix_size, c);

  std::free(a);
  std::free(b);
  std::free(c);

  double * d = new double[FLAGS_matrix_size * FLAGS_matrix_size];
  double * e = new double[FLAGS_matrix_size * FLAGS_matrix_size];
  double * f = new double[FLAGS_matrix_size * FLAGS_matrix_size];

  setMatric(FLAGS_matrix_size, d);
  setMatric(FLAGS_matrix_size, e);
  std::memset(f, 0, FLAGS_matrix_size * FLAGS_matrix_size * 8);
  printMatrix(FLAGS_matrix_size, f);

  dgemm_unaligned(FLAGS_matrix_size, d, e, f);

  printMatrix(FLAGS_matrix_size, f);

  delete []d;
  delete []e;
  delete []f;

  return 0;
}
