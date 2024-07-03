#include <check.h>

#include "s_object.h"

#define OK 0
#define ERROR 1
#define FILE_ERROR 2
#define EXTENSION_ERROR 4

const char *filename = "cube.obj";

START_TEST(shift_test_1) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  ck_assert_int_eq(er, OK);

  shift(s.matrix_3d.matrix, s.matrix_3d.rows, 1, 1, 1);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) + 1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) + 1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) + 1)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(shift_test_2) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  shift(s.matrix_3d.matrix, s.matrix_3d.rows, 30, 40, 50);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) + 30)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) + 40)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) + 50)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(shift_test_3) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  shift(s.matrix_3d.matrix, s.matrix_3d.rows, -24.004, 1000.9, -0.43);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) - 24.004)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) + 1000.9)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) - 0.43)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(shift_test_4) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  shift(s.matrix_3d.matrix, s.matrix_3d.rows, 0.05, 0, -0);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) + 0.05)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1))) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2))) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(scale_test_1) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  scale(s.matrix_3d.matrix, s.matrix_3d.rows, 2);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) * 2)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) * 2)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) * 2)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(scale_test_2) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  er += scale(s.matrix_3d.matrix, s.matrix_3d.rows, 0);
  ck_assert_int_eq(er, ERROR);
  remove_model(&s);
}

START_TEST(scale_test_3) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  er += scale(s.matrix_3d.matrix, s.matrix_3d.rows, 0.1);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) * 0.1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) * 0.1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) * 0.1)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(scale_test_4) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  er += scale(s.matrix_3d.matrix, s.matrix_3d.rows, 70.7);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) * 70.7)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) * 70.7)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) * 70.7)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_1) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double xd = 30;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, xd, 0, 0);
  xd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double y = *(s.matrix_3d.origin + i * 3 + 1),
           z = *(s.matrix_3d.origin + i * 3 + 2);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          *(s.matrix_3d.origin + i * 3)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (y * cos(xd) - sin(xd) * z)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (y * sin(xd) + cos(xd) * z)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_2) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double xd = -78;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, xd, 0, 0);
  xd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double y = *(s.matrix_3d.origin + i * 3 + 1),
           z = *(s.matrix_3d.origin + i * 3 + 2);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          *(s.matrix_3d.origin + i * 3)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (y * cos(xd) - sin(xd) * z)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (y * sin(xd) + cos(xd) * z)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_3) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double yd = 60;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, 0, yd, 0);
  yd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double x = *(s.matrix_3d.origin + i * 3),
           z = *(s.matrix_3d.origin + i * 3 + 2);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          *(s.matrix_3d.origin + i * 3 + 1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (x * cos(yd) + sin(yd) * z)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (z * cos(yd) - sin(yd) * x)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_4) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double yd = -10.567;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, 0, yd, 0);
  yd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double x = *(s.matrix_3d.origin + i * 3),
           z = *(s.matrix_3d.origin + i * 3 + 2);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          *(s.matrix_3d.origin + i * 3 + 1)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (x * cos(yd) + sin(yd) * z)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (z * cos(yd) - sin(yd) * x)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_5) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double zd = 90;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, 0, 0, zd);
  zd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double x = *(s.matrix_3d.origin + i * 3),
           y = *(s.matrix_3d.origin + i * 3 + 1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          *(s.matrix_3d.origin + i * 3 + 2)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (x * cos(zd) - sin(zd) * y)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (y * cos(zd) + sin(zd) * x)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_6) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double zd = -41.123;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, 0, 0, zd);
  zd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double x = *(s.matrix_3d.origin + i * 3),
           y = *(s.matrix_3d.origin + i * 3 + 1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          *(s.matrix_3d.origin + i * 3 + 2)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (x * cos(zd) - sin(zd) * y)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (y * cos(zd) + sin(zd) * x)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(turn_test_7) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  double xd = 60, yd = 30;
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, xd, yd, 0);
  xd *= M_PI / 180;
  yd *= M_PI / 180;
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    double x = *(s.matrix_3d.origin + i * 3);
    double y = *(s.matrix_3d.origin + i * 3 + 1),
           z = *(s.matrix_3d.origin + i * 3 + 2);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (y * cos(xd) - sin(xd) * z)) < 1e-7,
                     1);
    z = sin(xd) * y + cos(xd) * z;
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (x * cos(yd) + sin(yd) * z)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (z * cos(yd) - sin(yd) * x)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

START_TEST(test_alloc) {
  model s;
  int er = 0;
  er = create_model(&s, "qwe..asd");
  ck_assert_int_eq(er, FILE_ERROR);
  remove_model(&s);
}

START_TEST(test_extension) {
  model s;
  int er = 0;
  er = create_model(&s, "Makefile");
  ck_assert_int_eq(er, EXTENSION_ERROR);
  remove_model(&s);
}

START_TEST(all_test) {
  model s;
  int er = 0;
  er = create_model(&s, filename);
  turn(s.matrix_3d.matrix, s.matrix_3d.rows, 0, 0, 0);
  shift(s.matrix_3d.matrix, s.matrix_3d.rows, 30, 40, 50);
  scale(s.matrix_3d.matrix, s.matrix_3d.rows, 1);
  ck_assert_int_eq(er, OK);
  for (int i = 1; i < s.matrix_3d.rows; i++) {
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3) -
                          (*(s.matrix_3d.origin + i * 3) + 30)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 1) -
                          (*(s.matrix_3d.origin + i * 3 + 1) + 40)) < 1e-7,
                     1);
    ck_assert_int_eq(fabs(*(s.matrix_3d.matrix + i * 3 + 2) -
                          (*(s.matrix_3d.origin + i * 3 + 2) + 50)) < 1e-7,
                     1);
  }
  remove_model(&s);
}

int main() {
  Suite *s = suite_create("tests_model");
  SRunner *sr = srunner_create(s);
  srunner_set_fork_status(sr, CK_NOFORK);
  TCase *tc1 = tcase_create("model_test");
  suite_add_tcase(s, tc1);

  tcase_add_test(tc1, shift_test_1);
  tcase_add_test(tc1, shift_test_2);
  tcase_add_test(tc1, shift_test_3);
  tcase_add_test(tc1, shift_test_4);

  tcase_add_test(tc1, scale_test_1);
  tcase_add_test(tc1, scale_test_2);
  tcase_add_test(tc1, scale_test_3);
  tcase_add_test(tc1, scale_test_4);

  tcase_add_test(tc1, turn_test_1);
  tcase_add_test(tc1, turn_test_2);
  tcase_add_test(tc1, turn_test_3);
  tcase_add_test(tc1, turn_test_4);
  tcase_add_test(tc1, turn_test_5);
  tcase_add_test(tc1, turn_test_6);
  tcase_add_test(tc1, turn_test_7);

  tcase_add_test(tc1, all_test);
  tcase_add_test(tc1, test_alloc);
  tcase_add_test(tc1, test_extension);

  srunner_run_all(sr, CK_ENV);
  srunner_free(sr);
  return 0;
}
