#include "matrix_functions.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv) {
  if (argc < 4) {
    printf("Uso: %s <num_threads> <tamanho_matriz> <tamanho_bloco>\n", argv[0]);
    return 1;
  }

  int num_threads_arg = atoi(argv[1]);
  int S = atoi(argv[2]);
  int size_bucket = atoi(argv[3]);
  srand(42);

  int (*matrix_a)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_b)[S] = malloc(sizeof(int[S][S]));
  int (*matrix_c)[S] = malloc(sizeof(int[S][S]));

  fill_random_matrix(S, matrix_a);
  fill_random_matrix(S, matrix_b);
  zero_matrix(S, matrix_c);

  double start_time = omp_get_wtime();

  omp_set_num_threads(num_threads_arg);

#pragma omp parallel
  {
    int id = omp_get_thread_num();
    int total_threads = omp_get_num_threads();
    int num_chunks = (S + size_bucket - 1) / size_bucket;

    for (int chunk_id = id; chunk_id < num_chunks; chunk_id += total_threads) {
      int start_row = chunk_id * size_bucket;
      int end_row = start_row + size_bucket;
      if (end_row > S) {
        end_row = S;
      }

      for (int i = start_row; i < end_row; i++) {
        for (int j = 0; j < S; j++) {
          for (int k = 0; k < S; k++) {
            matrix_c[i][j] += matrix_a[i][k] * matrix_b[k][j];
          }
        }
      }
    }
  }

  double end_time = omp_get_wtime();
  double time_taken = end_time - start_time;

  printf("%f\n", time_taken);

  free(matrix_a);
  free(matrix_b);

  FILE *file = fopen("./Results/resultado_manual_schedule", "w");
  if (file) {
    for (size_t x = 0; x < S; x++) {
      for (size_t y = 0; y < S; y++) {
        fwrite(&matrix_c[x][y], sizeof(int), 1, file);
      }
    }
    fclose(file);
  }

  free(matrix_c);

  return 0;
}
