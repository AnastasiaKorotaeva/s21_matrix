#include "s21_matrix.h"

int s21_inverse_matrix(matrix_t *A,
                       matrix_t *result) {  // поиск обратной матрицы
  matrix_t dop_matrix_calc = {0};
  matrix_t dop_matrix_trns = {0};
  int err = NORMAL;
  if (check(A) && result) {
    if ((*A).rows == (*A).columns) {
      if (((*A).rows) == 1) {
        err = s21_create_matrix(1, 1, result);
        if (err == NORMAL) {
          if (fabs((*A).matrix[0][0]) > EPS) {
            (*result).matrix[0][0] = 1.0 / (*A).matrix[0][0];
          } else
            err = NOCALC;
        }
      } else {  // 1/det(A) * M^T. (M^T. = Транспонированная матрица
                // алгебраических дополнений)
        double determinant = 0;
        s21_determinant(A, &determinant);
        if (fabs(determinant) > EPS)  // Проверка на ненулевой определитель
        {
          s21_calc_complements(A, &dop_matrix_calc);
          s21_transpose(&dop_matrix_calc, &dop_matrix_trns);
          s21_mult_number(&dop_matrix_trns, 1.0 / determinant, result);
          s21_remove_matrix(&dop_matrix_calc);
          s21_remove_matrix(&dop_matrix_trns);
        } else
          err = NOCALC;
      }
    } else
      err = NOCALC;
  } else
    err = NOCORRECT;
  return err;
}
