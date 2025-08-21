#include "matrix_functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
  srand(42);
  int (*matrix_a)[N] = malloc(sizeof(int[N][N]));
  int (*matrix_b)[N] = malloc(sizeof(int[N][N]));
  int (*matrix_c)[N] = malloc(sizeof(int[N][N]));

  fill_random_matrix(matrix_a);
  fill_random_matrix(matrix_b);
  zero_matrix(matrix_c);

  clock_t start_time = clock();

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
      }
    }
  }

  clock_t end_time = clock();
  double elapsed_time = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;

  printf("Tempo de execucao (sequencial): %f segundos\n", elapsed_time);

  free(matrix_a);
  free(matrix_b);

  FILE *file = fopen("resultado_sequencial", "w");
  for (size_t x = 0; x < N; x++) {
    for (size_t y = 0; y < N; y++) {
      fwrite(&matrix_c[x][y], sizeof(int), 1, file);
    }
  }
  fclose(file);

  free(matrix_c);
  return 0;
}
