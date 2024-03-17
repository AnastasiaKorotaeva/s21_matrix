#include "s21_matrix.h"

int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result) {  // вычитание матриц
  int err = NORMAL;
  if (check(A) && check(B) && result) {
    if ((*A).rows == (*B).rows && (*A).columns == (*B).columns) {
      err = s21_create_matrix((*A).rows, (*A).columns, result);
      if (err == NORMAL) {
        for (int i = 0; i < (*A).rows; i++) {
          for (int j = 0; j < (*A).columns; j++) {
            (*result).matrix[i][j] = (*A).matrix[i][j] - (*B).matrix[i][j];
          }
        }
      }
    } else
      err = NOCALC;
  } else
    err = NOCORRECT;
  return err;
}
