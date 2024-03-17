#include "s21_matrix.h"

int s21_calc_complements(
    matrix_t *A,
    matrix_t *result) {  // вычисление матрицы алгребраический дополнений
  int err = NORMAL;
  if (check(A) && result) {
    if ((*A).rows == (*A).columns) {
      s21_create_matrix((*A).rows, (*A).columns, result);
      if (err == NORMAL) {
        for (int i = 0; i < (*A).rows; i++) {
          for (int j = 0; j < (*A).columns; j++) {
            matrix_t minor = {0};
            err = s21_create_matrix((*A).rows - 1, (*A).columns - 1, &minor);
            if (err == NORMAL) {
              calc_minor(i, j, A, &minor);
              double minorDeterminant = 0;
              s21_determinant(&minor, &minorDeterminant);
              int sign = (i + j) % 2 == 0 ? 1 : -1;
              (*result).matrix[i][j] = sign * minorDeterminant;
              s21_remove_matrix(&minor);
            }
          }
        }
      }
    } else
      err = NOCALC;
  } else
    err = NOCORRECT;
  return err;
}
