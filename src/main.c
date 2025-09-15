#include "matrix_functions.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Falta o numero da matriz");
    return 1;
  }
  int S = atoi(argv[1]);

  srand(42);
  int (*matrix_a)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_b)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_c)[S] = malloc(sizeof(int[S][S]));
  fill_random_matrix(S, matrix_a);
  fill_random_matrix(S, matrix_b);
  zero_matrix(S, matrix_c);

  double start_time = omp_get_wtime();

  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
      for (int k = 0; k < S; k++) {
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
      }
    }
  }

  double end_time = omp_get_wtime();
  double time = end_time - start_time;

  printf("Tempo de execucao (sequencial): %f segundos\n", time);

  free(matrix_a);
  free(matrix_b);

  FILE *file = fopen("resultado_sequencial", "w");
  for (size_t x = 0; x < S; x++) {
    for (size_t y = 0; y < S; y++) {
      fwrite(&matrix_c[x][y], sizeof(int), 1, file);
    }
  }
  fclose(file);

  free(matrix_c);
  printf("%f", time);
  return 0;
}
