#include "s21_matrix.h"

int s21_transpose(matrix_t *A, matrix_t *result) {  // транспонирование матрицы
  int err = NOCORRECT;
  if (check(A) && result) {
    (*result).rows = (*A).columns;
    (*result).columns = (*A).rows;
    (*result).matrix = (double **)calloc((*result).rows, sizeof(double *));
    if ((*result).matrix != NULL) {
      for (int i = 0; i < (*result).rows; i++) {
        (*result).matrix[i] =
            (double *)calloc((*result).columns, sizeof(double));
        if ((*result).matrix[i] != NULL) {
          err = NORMAL;
        }
        if (err == NORMAL) {
          for (int j = 0; j < (*result).columns; j++) {
            (*result).matrix[i][j] = (*A).matrix[j][i];
          }
        }
      }
    }
  } else
    err = NOCORRECT;
  return err;
}
