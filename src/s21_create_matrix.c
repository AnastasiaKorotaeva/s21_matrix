#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns,
                      matrix_t *result) {  // создание матрицы
  int err = NOCORRECT;
  if (rows > 0 && columns > 0 && result) {
    (*result).rows = rows;
    (*result).columns = columns;
    (*result).matrix = (double **)calloc(rows, sizeof(double *));
    if ((*result).matrix != NULL) {
      for (int i = 0; i < (*result).rows; i++) {
        (*result).matrix[i] = (double *)calloc(columns, sizeof(double));
        if ((*result).matrix[i] != NULL) {
          err = NORMAL;
        }
      }
    }
  }
  return err;
}
