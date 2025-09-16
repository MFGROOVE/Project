#include "matrix_functions.h"
#include <stddef.h>
#include <stdlib.h>

void fill_random_matrix(int S, int matrix[S][S]) {
  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
      matrix[i][j] = rand() % 100;
    }
  }
}

void zero_matrix(int S, int matrix[S][S]) {
  for (int i = 0; i < S; i++) {
    for (int j = 0; j < S; j++) {
      matrix[i][j] = 0;
    }
  }
}
