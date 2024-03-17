#include "s21_matrix.h"

void s21_remove_matrix(matrix_t *matrix) {  // очистка и уничтожение матрицы
  if (matrix == NULL || ((*matrix).matrix) == NULL) {
    return;
  } else {
    for (int i = 0; i < (*matrix).rows; i++) {
      if ((*matrix).matrix[i] != NULL) free((*matrix).matrix[i]);
    }
    free((*matrix).matrix);
  }
  (*matrix).rows = 0;
  (*matrix).columns = 0;
  (*matrix).matrix = NULL;
}