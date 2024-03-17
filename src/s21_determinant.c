#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {  //вычисление определителя
  int err = NORMAL;
  if (check(A)) {
    if ((*A).rows == (*A).columns) {
      int sign = 1;
      *result = 0;
      matrix_t minor = {0};
      if ((*A).rows == 1) {  // det(A) = a
        *result = (*A).matrix[0][0];
      } else if ((*A).rows == 2) {  // //det(A) = a00*a11 - a01*a10
        *result = (*A).matrix[0][0] * (*A).matrix[1][1] -
                  (*A).matrix[0][1] * (*A).matrix[1][0];
      } else {  // det(A) = a00 * det(minor00) - a01 * det(minor01) + a03 *
                // det(minor03) - ... + (-1)^(n+1) * a0n * det(minorn0n)
        err = s21_create_matrix((*A).rows - 1, (*A).columns - 1, &minor);
        if (err == NORMAL) {
          for (int i = 0; i < (*A).rows; i++) {
            calc_minor(0, i, A, &minor);
            double minorResult = 0;
            s21_determinant(&minor, &minorResult);
            *result += sign * (*A).matrix[0][i] * minorResult;
            sign = -sign;
          }
          s21_remove_matrix(&minor);
        }
      }
    } else
      err = NOCALC;
  } else
    err = NOCORRECT;
  return err;
}
