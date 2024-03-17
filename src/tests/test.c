#include "test.h"

START_TEST(fun_s21_create_matrix) {
  matrix_t matrix_1;
  int result1 = s21_create_matrix(-1, 2, &matrix_1);
  int result2 = s21_create_matrix(1, -2, &matrix_1);
  int result3 = s21_create_matrix(-1, -2, &matrix_1);
  int result4 = s21_create_matrix(1, 2, &matrix_1);
  int result5 = s21_create_matrix(1, 2, NULL);
  s21_remove_matrix(&matrix_1);
  ck_assert_int_eq(NOCORRECT, result1);
  ck_assert_int_eq(NOCORRECT, result2);
  ck_assert_int_eq(NOCORRECT, result3);
  ck_assert_int_eq(NORMAL, result4);
  ck_assert_int_eq(NOCORRECT, result5);
}
END_TEST

START_TEST(fun_s21_remove_matrix) {
  matrix_t matrix_1;
  int err = s21_create_matrix(3, 3, &matrix_1);
  s21_remove_matrix(&matrix_1);
  if (matrix_1.matrix != NULL) {
    err = NOCORRECT;
  }
  ck_assert_int_eq(NORMAL, err);

  matrix_t *matrix_2 = NULL;
  s21_remove_matrix(matrix_2);
}
END_TEST

START_TEST(fun_s21_eq_matrix) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t matrix_2;

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &matrix_2);

  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(SUCCESS, err);

  err = s21_eq_matrix(&matrix_1, NULL);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.matrix[0][0] = 6;
  matrix_1.matrix[0][1] = 4;
  matrix_1.matrix[0][2] = 7;
  matrix_1.matrix[0][3] = 1;
  matrix_1.matrix[1][0] = 5;
  matrix_1.matrix[1][1] = 12;
  matrix_1.matrix[1][2] = 9;
  matrix_1.matrix[1][3] = 0;
  matrix_1.matrix[2][0] = 4;
  matrix_1.matrix[2][1] = 7;
  matrix_1.matrix[2][2] = 2;
  matrix_1.matrix[2][3] = -6;
  matrix_1.matrix[3][0] = 2;
  matrix_1.matrix[3][1] = 6;
  matrix_1.matrix[3][2] = -1;
  matrix_1.matrix[3][3] = 3;

  matrix_2.matrix[0][0] = 6;
  matrix_2.matrix[0][1] = 4;
  matrix_2.matrix[0][2] = 7;
  matrix_2.matrix[0][3] = 1;
  matrix_2.matrix[1][0] = 5;
  matrix_2.matrix[1][1] = 12;
  matrix_2.matrix[1][2] = 9;
  matrix_2.matrix[1][3] = 0;
  matrix_2.matrix[2][0] = 4;
  matrix_2.matrix[2][1] = 7;
  matrix_2.matrix[2][2] = 2;
  matrix_2.matrix[2][3] = -6;
  matrix_2.matrix[3][0] = 2;
  matrix_2.matrix[3][1] = 6;
  matrix_2.matrix[3][2] = -1;
  matrix_2.matrix[3][3] = 3;

  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(SUCCESS, err);

  matrix_1.matrix[1][1] = 8.0;
  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(FAILURE, err);

  matrix_2.matrix[1][1] = 5.0;
  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.columns = 0;
  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(FAILURE, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &matrix_2);

  matrix_1.matrix[0][0] = 11.00000011;
  matrix_1.matrix[0][1] = 7.0;
  matrix_1.matrix[1][0] = 2.0;
  matrix_1.matrix[1][1] = 9.0;

  matrix_2.matrix[0][0] = 11.00000012;
  matrix_2.matrix[0][1] = 7.0;
  matrix_2.matrix[1][0] = 2.0;
  matrix_2.matrix[1][1] = 9.0;

  err = s21_eq_matrix(&matrix_1, &matrix_2);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
}
END_TEST

START_TEST(fun_s21_sum_matrix) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t matrix_2;
  matrix_t result;
  matrix_t res_matr12;

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &matrix_2);
  s21_create_matrix(2, 2, &res_matr12);

  err = s21_sum_matrix(&matrix_1, &matrix_2, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_sum_matrix(&matrix_1, NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_sum_matrix(NULL, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  matrix_1.matrix[0][0] = 1.2;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[1][0] = 3;
  matrix_1.matrix[1][1] = 4;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[0][1] = 2;
  matrix_2.matrix[1][0] = 3;
  matrix_2.matrix[1][1] = 4;

  res_matr12.matrix[0][0] = 2.2;
  res_matr12.matrix[0][1] = 4;
  res_matr12.matrix[1][0] = 6;
  res_matr12.matrix[1][1] = 8;

  err = s21_sum_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  matrix_1.matrix[0][0] = 1.456;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[1][0] = 3;
  matrix_1.matrix[1][1] = 5;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[0][1] = 2;
  matrix_2.matrix[1][0] = 3;
  matrix_2.matrix[1][1] = 4;

  res_matr12.matrix[0][0] = 2.456;
  res_matr12.matrix[0][1] = 4;
  res_matr12.matrix[1][0] = 32;
  res_matr12.matrix[1][1] = 9;

  err = s21_sum_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.columns = -7;
  err = s21_sum_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_create_matrix(2, 8, &matrix_1);
  err = s21_sum_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr12);
}
END_TEST

START_TEST(fun_s21_sub_matrix) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t matrix_2;
  matrix_t result;
  matrix_t res_matr12;

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &matrix_2);
  s21_create_matrix(2, 2, &res_matr12);

  err = s21_sub_matrix(&matrix_1, &matrix_2, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_sub_matrix(&matrix_1, NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_sub_matrix(NULL, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  matrix_1.matrix[0][0] = 5.2;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[1][0] = 5;
  matrix_1.matrix[1][1] = 4;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[0][1] = 2;
  matrix_2.matrix[1][0] = 3;
  matrix_2.matrix[1][1] = 8;

  res_matr12.matrix[0][0] = 4.2;
  res_matr12.matrix[0][1] = 0;
  res_matr12.matrix[1][0] = 2;
  res_matr12.matrix[1][1] = -4;

  err = s21_sub_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  matrix_1.matrix[0][0] = 1.456;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[1][0] = 3;
  matrix_1.matrix[1][1] = 5;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[0][1] = 2;
  matrix_2.matrix[1][0] = 3;
  matrix_2.matrix[1][1] = 4;

  res_matr12.matrix[0][0] = 2.456;
  res_matr12.matrix[0][1] = 4;
  res_matr12.matrix[1][0] = 32;
  res_matr12.matrix[1][1] = 9;

  err = s21_sub_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.columns = -7;
  err = s21_sub_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_create_matrix(2, 8, &matrix_1);
  err = s21_sub_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr12);
}
END_TEST

START_TEST(fun_s21_mult_matrix) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t matrix_2;
  matrix_t result;
  matrix_t res_matr12;

  s21_create_matrix(3, 1, &matrix_1);
  s21_create_matrix(1, 3, &matrix_2);
  s21_create_matrix(3, 3, &res_matr12);

  err = s21_mult_matrix(NULL, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_mult_matrix(&matrix_1, NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_mult_matrix(&matrix_1, &matrix_2, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  matrix_1.matrix[0][0] = 1.2;
  matrix_1.matrix[1][0] = 3;
  matrix_1.matrix[2][0] = 0;

  matrix_2.matrix[0][0] = 1;
  matrix_2.matrix[0][1] = 2;
  matrix_2.matrix[0][2] = 3.4;

  res_matr12.matrix[0][0] = 1.2;
  res_matr12.matrix[0][1] = 2.4;
  res_matr12.matrix[0][2] = 4.08;
  res_matr12.matrix[1][0] = 3;
  res_matr12.matrix[1][1] = 6;
  res_matr12.matrix[1][2] = 10.2;
  res_matr12.matrix[2][0] = 0;
  res_matr12.matrix[2][1] = 0;
  res_matr12.matrix[2][2] = 0;

  err = s21_mult_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  res_matr12.matrix[2][2] = 10;
  err = s21_mult_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr12);
  ck_assert_int_eq(FAILURE, err);

  s21_remove_matrix(&matrix_2);
  matrix_2.rows = -1;
  err = s21_mult_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_2);
  s21_create_matrix(5, 3, &matrix_2);
  matrix_2.rows = 5;
  err = s21_mult_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_2);
  s21_create_matrix(4, 4, &matrix_2);
  err = s21_mult_matrix(&matrix_1, &matrix_2, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&matrix_2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr12);
}
END_TEST

START_TEST(fun_s21_mult_number) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t result;
  matrix_t res_matr1;

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &res_matr1);

  err = s21_mult_number(NULL, 0, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_mult_number(&matrix_1, 0, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  matrix_1.matrix[0][0] = 6.7;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[1][0] = -4;
  matrix_1.matrix[1][1] = 1;

  res_matr1.matrix[0][0] = 13.4;
  res_matr1.matrix[0][1] = 10;
  res_matr1.matrix[1][0] = -8;
  res_matr1.matrix[1][1] = 2;

  err = s21_mult_number(&matrix_1, 2.0, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  res_matr1.matrix[0][0] = 2.2;
  res_matr1.matrix[0][1] = 4.7;
  res_matr1.matrix[1][0] = 50;
  res_matr1.matrix[1][1] = 8;

  err = s21_mult_number(&matrix_1, 2.0, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.columns = -5;
  err = s21_mult_number(&matrix_1, 2.0, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr1);
}
END_TEST

START_TEST(fun_s21_transpose) {
  int err = 0;
  matrix_t matrix_1;
  matrix_t result;
  matrix_t res_matr1;

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(2, 3, &res_matr1);

  err = s21_transpose(NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_transpose(&matrix_1, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  matrix_1.matrix[0][0] = 3.7;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = -2;
  matrix_1.matrix[2][0] = 0.3;
  matrix_1.matrix[2][1] = 9;

  res_matr1.matrix[0][0] = 3.7;
  res_matr1.matrix[0][1] = 1;
  res_matr1.matrix[0][2] = 0.3;
  res_matr1.matrix[1][0] = 5;
  res_matr1.matrix[1][1] = -2;
  res_matr1.matrix[1][2] = 9;

  err = s21_transpose(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  res_matr1.matrix[1][2] = 10;
  err = s21_transpose(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(FAILURE, err);

  matrix_1.columns = 0;
  err = s21_transpose(&matrix_1, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr1);
}
END_TEST

START_TEST(fun_s21_determinant) {
  int err = 0;
  matrix_t matrix_1;
  double result = 0;

  s21_create_matrix(3, 2, &matrix_1);

  err = s21_determinant(NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_create_matrix(4, 4, &matrix_1);
  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[0][3] = 3;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = -5;
  matrix_1.matrix[1][2] = 3.3;
  matrix_1.matrix[1][3] = 1.3;
  matrix_1.matrix[2][0] = -8.3;
  matrix_1.matrix[2][1] = -1;
  matrix_1.matrix[2][2] = 0;
  matrix_1.matrix[2][3] = -1;
  matrix_1.matrix[3][0] = -2;
  matrix_1.matrix[3][1] = 6;
  matrix_1.matrix[3][2] = 7;
  matrix_1.matrix[3][3] = 3;
  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  ck_assert_ldouble_eq_tol(result, 599.6, EPS);

  s21_remove_matrix(&matrix_1);
  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 4;
  matrix_1.matrix[1][1] = 5;
  matrix_1.matrix[1][2] = 6;
  matrix_1.matrix[2][0] = 7;
  matrix_1.matrix[2][1] = 8;
  matrix_1.matrix[2][2] = 9;
  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  ck_assert_ldouble_eq_tol(result, 0, EPS);

  s21_remove_matrix(&matrix_1);
  s21_create_matrix(2, 2, &matrix_1);
  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[1][0] = 5;
  matrix_1.matrix[0][1] = 3;
  matrix_1.matrix[1][1] = 1;

  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  ck_assert_ldouble_eq_tol(result, -13, EPS);

  s21_remove_matrix(&matrix_1);
  matrix_1.rows = -1;
  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_create_matrix(1, 1, &matrix_1);
  matrix_1.matrix[0][0] = 2;
  err = s21_determinant(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  ck_assert_ldouble_eq_tol(result, 2, EPS);

  s21_remove_matrix(&matrix_1);
}
END_TEST

START_TEST(fun_s21_calc_complements) {
  matrix_t matrix_1;
  matrix_t result;
  matrix_t res_matr1;
  int err = 0;

  s21_create_matrix(3, 2, &matrix_1);
  s21_create_matrix(3, 3, &res_matr1);

  err = s21_calc_complements(NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_calc_complements(&matrix_1, NULL);
  ck_assert_int_eq(NOCORRECT, err);

  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);

  s21_create_matrix(2, 2, &matrix_1);
  s21_create_matrix(2, 2, &res_matr1);

  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[0][1] = 7;
  matrix_1.matrix[1][0] = 8;
  matrix_1.matrix[1][1] = 1;

  res_matr1.matrix[0][0] = 1;
  res_matr1.matrix[0][1] = -8;
  res_matr1.matrix[1][0] = -7;
  res_matr1.matrix[1][1] = 2;

  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);
  s21_remove_matrix(&result);

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &res_matr1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[0][1] = 2;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[1][0] = 0;
  matrix_1.matrix[1][1] = 4;
  matrix_1.matrix[1][2] = 2;
  matrix_1.matrix[2][0] = 5;
  matrix_1.matrix[2][1] = 2;
  matrix_1.matrix[2][2] = 1;

  res_matr1.matrix[0][0] = 0;
  res_matr1.matrix[0][1] = 10;
  res_matr1.matrix[0][2] = -20;
  res_matr1.matrix[1][0] = 4;
  res_matr1.matrix[1][1] = -14;
  res_matr1.matrix[1][2] = 8;
  res_matr1.matrix[2][0] = -8;
  res_matr1.matrix[2][1] = -2;
  res_matr1.matrix[2][2] = 4;

  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);
  s21_remove_matrix(&result);

  s21_create_matrix(4, 4, &matrix_1);
  s21_create_matrix(4, 4, &res_matr1);
  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[0][1] = 5;
  matrix_1.matrix[0][2] = 3;
  matrix_1.matrix[0][3] = 3;
  matrix_1.matrix[1][0] = 1;
  matrix_1.matrix[1][1] = -5;
  matrix_1.matrix[1][2] = 3.3;
  matrix_1.matrix[1][3] = 1.3;
  matrix_1.matrix[2][0] = -8.3;
  matrix_1.matrix[2][1] = -1;
  matrix_1.matrix[2][2] = 0;
  matrix_1.matrix[2][3] = -1;
  matrix_1.matrix[3][0] = -2;
  matrix_1.matrix[3][1] = 6;
  matrix_1.matrix[3][2] = 7;
  matrix_1.matrix[3][3] = 3;

  res_matr1.matrix[0][0] = -54;
  res_matr1.matrix[0][1] = -20.24;
  res_matr1.matrix[0][2] = -198.84;
  res_matr1.matrix[0][3] = 468.44;
  res_matr1.matrix[1][0] = -5;
  res_matr1.matrix[1][1] = -79.6;
  res_matr1.matrix[1][2] = 14.9;
  res_matr1.matrix[1][3] = 121.1;
  res_matr1.matrix[2][0] = -92;
  res_matr1.matrix[2][1] = -25.6;
  res_matr1.matrix[2][2] = -85.6;
  res_matr1.matrix[2][3] = 189.6;
  res_matr1.matrix[3][0] = 25.5;
  res_matr1.matrix[3][1] = 46.2;
  res_matr1.matrix[3][2] = 163.85;
  res_matr1.matrix[3][3] = -257.85;

  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);

  res_matr1.matrix[1][2] = 100;
  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(FAILURE, err);

  s21_remove_matrix(&result);
  s21_remove_matrix(&matrix_1);

  matrix_1.rows = -3;
  err = s21_calc_complements(&matrix_1, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr1);
}
END_TEST

START_TEST(fun_s21_inverse_matrix) {
  matrix_t matrix_1;
  matrix_t result;
  matrix_t res_matr1;
  int err = 0;

  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &res_matr1);
  matrix_1.matrix[0][0] = -14;
  res_matr1.matrix[0][0] = -0.0714285;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);
  s21_remove_matrix(&result);

  s21_create_matrix(1, 1, &matrix_1);
  s21_create_matrix(1, 1, &res_matr1);
  matrix_1.matrix[0][0] = 0.0000008;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);
  s21_remove_matrix(&result);

  s21_create_matrix(3, 2, &matrix_1);

  err = s21_inverse_matrix(NULL, &result);
  ck_assert_int_eq(NOCORRECT, err);
  err = s21_inverse_matrix(&matrix_1, NULL);
  ck_assert_int_eq(NOCORRECT, err);
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);

  s21_create_matrix(3, 3, &matrix_1);
  matrix_1.matrix[0][0] = 1;
  matrix_1.matrix[1][0] = 2;
  matrix_1.matrix[2][0] = 3;
  matrix_1.matrix[0][1] = 4;
  matrix_1.matrix[1][1] = 5;
  matrix_1.matrix[2][1] = 6;
  matrix_1.matrix[0][2] = 7;
  matrix_1.matrix[1][2] = 8;
  matrix_1.matrix[2][2] = 9;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&res_matr1);

  s21_create_matrix(3, 3, &matrix_1);
  s21_create_matrix(3, 3, &res_matr1);

  matrix_1.matrix[0][0] = 2;
  matrix_1.matrix[1][0] = 5;
  matrix_1.matrix[2][0] = 7;
  matrix_1.matrix[0][1] = 6;
  matrix_1.matrix[1][1] = 3;
  matrix_1.matrix[2][1] = 4;
  matrix_1.matrix[0][2] = 5;
  matrix_1.matrix[1][2] = -2;
  matrix_1.matrix[2][2] = -3;

  res_matr1.matrix[0][0] = 1;
  res_matr1.matrix[1][0] = -1;
  res_matr1.matrix[2][0] = 1;
  res_matr1.matrix[0][1] = -38;
  res_matr1.matrix[1][1] = 41;
  res_matr1.matrix[2][1] = -34;
  res_matr1.matrix[0][2] = 27;
  res_matr1.matrix[1][2] = -29;
  res_matr1.matrix[2][2] = 24;

  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&result);
  res_matr1.matrix[2][2] = -14;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NORMAL, err);
  err = s21_eq_matrix(&result, &res_matr1);
  ck_assert_int_eq(FAILURE, err);

  s21_remove_matrix(&result);
  matrix_1.matrix[0][2] = 0;
  matrix_1.matrix[1][2] = 0;
  matrix_1.matrix[2][2] = 0;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NOCALC, err);

  s21_remove_matrix(&matrix_1);
  matrix_1.rows = -2;
  err = s21_inverse_matrix(&matrix_1, &result);
  ck_assert_int_eq(NOCORRECT, err);

  s21_remove_matrix(&matrix_1);
  s21_remove_matrix(&res_matr1);
  s21_remove_matrix(&result);
}
END_TEST

Suite *suite_fun_matrix(void) {
  Suite *suite;
  TCase *all_tcase;

  suite = suite_create("fun_matrix");
  all_tcase = tcase_create("All_case");

  tcase_add_test(all_tcase, fun_s21_create_matrix);
  tcase_add_test(all_tcase, fun_s21_remove_matrix);
  tcase_add_test(all_tcase, fun_s21_eq_matrix);
  tcase_add_test(all_tcase, fun_s21_sum_matrix);
  tcase_add_test(all_tcase, fun_s21_sub_matrix);
  tcase_add_test(all_tcase, fun_s21_mult_matrix);
  tcase_add_test(all_tcase, fun_s21_mult_number);
  tcase_add_test(all_tcase, fun_s21_transpose);
  tcase_add_test(all_tcase, fun_s21_determinant);
  tcase_add_test(all_tcase, fun_s21_calc_complements);
  tcase_add_test(all_tcase, fun_s21_inverse_matrix);

  suite_add_tcase(suite, all_tcase);
  return suite;
}

int main(void) {
  int failed_count;
  Suite *suite;
  SRunner *srunner;

  suite = suite_fun_matrix();
  srunner = srunner_create(suite);

  srunner_set_fork_status(srunner, CK_NOFORK);
  srunner_run_all(srunner, CK_NORMAL);
  failed_count = srunner_ntests_failed(srunner);
  srunner_free(srunner);
  return (failed_count == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
