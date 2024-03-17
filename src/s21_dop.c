#include "s21_matrix.h"

int check(matrix_t *matrix) {  // проверка матрицы на корректность
  int err = 0;
  if (matrix != NULL && (*matrix).rows > 0 && (*matrix).columns > 0 &&
      (*matrix).matrix != NULL) {
    err = 1;
  }
  return err;
}

int calc_minor(int row, int column, matrix_t *A,
               matrix_t *result) {  // получение матрицы без строки и столбца с
                                    // элементом необходимого минора
  int minorRow = 0, minorColumn = 0;
  for (int i = 0; i < (*A).rows; i++) {
    for (int j = 0; j < (*A).columns; j++) {
      if (i != row && j != column) {
        (*result).matrix[minorRow][minorColumn++] = (*A).matrix[i][j];
        if (minorColumn == (*result).columns) {  // пока столбцы не закончились
          minorRow++;
          minorColumn = 0;
        }
      }
    }
  }
  return 0;
}