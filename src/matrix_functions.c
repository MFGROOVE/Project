#include "matrix_functions.h"
#include <stdlib.h>

void fill_random_matrix(int matrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = rand() % 100;
    }
  }
}

void zero_matrix(int matrix[N][N]) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      matrix[i][j] = 0;
    }
  }
}
