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

    for (int i = id; i < N; i += n) {
      for (int j = 0; j < N; j++) {
#pragma omp simd
        for (int k = 0; k < N; k++) {
          matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        }
      }
    }
  }

  double end_time = omp_get_wtime();
  printf("Tempo de execucao (metodo ID + SIMD): %f segundos\n",
         end_time - start_time);
  free(matrix_a);
  free(matrix_b);
  FILE *file = fopen("Metodo_id_SIMD", "w");
  for (size_t x = 0; x < N; x++) {
    for (size_t y = 0; y < N; y++) {
      fwrite(&matrix_c[x][y], sizeof(int), 1, file);
    }
  }

  free(matrix_c);
  return 0;
}
