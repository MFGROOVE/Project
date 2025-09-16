#include "matrix_functions.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("Faltam argumentos para o codigo. Os argumentos são:\n1) numero de "
           "threads\n2) tamanho da matriz\n");
    return 1;
  }

  srand(42);

  int num_threads = atoi(argv[1]);
  int S = atoi(argv[2]);
  int (*matrix_a)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_b)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_c)[S] = malloc(sizeof(int[S][S]));

  fill_random_matrix(S, matrix_a);
  fill_random_matrix(S, matrix_b);
  zero_matrix(S, matrix_c);

  double start_time = omp_get_wtime();

  omp_set_num_threads(num_threads);

#pragma omp parallel
  {
    int n = omp_get_num_threads();
    int id = omp_get_thread_num();

    for (int i = id; i < S; i += n) {
      for (int j = 0; j < S; j++) {
#pragma omp simd
        for (int k = 0; k < S; k++) {
          matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
        }
      }
    }
  }

  double end_time = omp_get_wtime();
  printf("Tempo de execucao (metodo ID + SIMD): %f segundos\n",
         end_time - start_time);

  double time = end_time - start_time;

  free(matrix_a);
  free(matrix_b);

  FILE *file = fopen("Metodo_id_SIMD", "w");
  for (size_t x = 0; x < S; x++) {
    for (size_t y = 0; y < S; y++) {
      fwrite(&matrix_c[x][y], sizeof(int), 1, file);
    }
  }
  fclose(file);
  printf("%f", time);
  free(matrix_c);
  return 0;
}
