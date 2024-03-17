#include "s21_matrix.h"

int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result) {  // умножение матрицы на число
  int err = NORMAL;
  if (check(A) && result) {
    err = s21_create_matrix((*A).rows, (*A).columns, result);
    if (err == NORMAL) {
      for (int i = 0; i < (*A).rows; i++) {
        for (int j = 0; j < (*A).columns; j++) {
          (*result).matrix[i][j] = (*A).matrix[i][j] * number;
        }
      }
    }
  } else
    err = NOCORRECT;
  return err;
}
