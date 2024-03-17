#include "s21_matrix.h"

int s21_eq_matrix(matrix_t *A, matrix_t *B) {  // сравнение матрицы
  int err = SUCCESS;
  if (check(A) && check(B) && ((*A).rows) == ((*B).rows) &&
      ((*A).columns) == ((*B).columns)) {
    for (int i = 0; i < (*A).rows; i++)
      for (int j = 0; j < (*A).columns; j++) {
        if (fabs(((*A).matrix[i][j]) - ((*B).matrix[i][j])) > EPS) {
          err = FAILURE;
        }
      }
  } else
    err = FAILURE;
  return err;
}