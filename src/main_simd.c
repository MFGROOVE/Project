#include "matrix_functions.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(42); /* As matrizes são aleátorias,mas,
     são controladas pela seed,
     assim todos os algoritmos realizam a multiplicação com a mesma matriz */

  int (*matrix_a)[N] = malloc(sizeof(int[N][N]));
  int (*matrix_b)[N] = malloc(sizeof(int[N][N]));
  int (*matrix_c)[N] = malloc(sizeof(int[N][N]));

  fill_random_matrix(matrix_a);
  fill_random_matrix(matrix_b);
  zero_matrix(matrix_c);

  double start_time = omp_get_wtime();

#pragma omp parallel
  {
    int n = omp_get_num_threads();
    int id = omp_get_thread_num();
    int bucket = N / n;
    int start = id * bucket;
    int end;

    if (id == n - 1) {
      end = N;
    } else {
      end = start + bucket;
    }

    for (int i = start; i < end; i++) {
      for (int j = 0; j < N; j++) {
#pragma omp simd
        for (int k = 0; k < N; k++) {
          matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        }
      }
    }
  }

  double end_time = omp_get_wtime();
  printf("Tempo de execucao (metodo buckets + SIMD): %f segundos\n",
         end_time - start_time);
  free(matrix_a);
  free(matrix_b);
  free(matrix_c);
  return 0;
}
