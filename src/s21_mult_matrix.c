#include "s21_matrix.h"

int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result) {  // умножение матриц
  int err = NORMAL;
  if (check(A) && check(B) && result) {
    if ((*A).columns ==
        (*B).rows) {  // кол-во столбцов A обязательно равно кол-во строк B
      err =
          s21_create_matrix((*A).rows, (*B).columns,
                            result);  // итоговая матрица = A строк и B столбцов
      if (err == NORMAL) {
        for (int i = 0; i < (*A).rows; i++) {
          for (int j = 0; j < (*B).columns; j++) {
            for (int k = 0; k < (*A).columns; k++) {
              (*result).matrix[i][j] += (*A).matrix[i][k] * (*B).matrix[k][j];
              // элемент строки A * элемент столбца B
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
