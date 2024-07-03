#include "s_object.h"

/* Перемещение модели по осям */
void shift(double *matrix_v, int rows_count, double x, double y, double z) {
  for (int i = 1; i < rows_count; i++) {
    *(matrix_v + i * 3) += x;
    *(matrix_v + i * 3 + 1) += y;
    *(matrix_v + i * 3 + 2) += z;
  }
}

/* Поворот модели по осям (угол в градусах) */
void turn(double *matrix_v, int rows_count, double xd, double yd, double zd) {
  double x0 = 0, y0 = 0, z0 = 0;
  xd *= M_PI / 180;  // перевод градусов в радианы
  yd *= M_PI / 180;  // перевод градусов в радианы
  zd *= M_PI / 180;  // перевод градусов в радианы
  if (fabs(0. - xd) > 1e-7) {
    // Поворот по оси X
    for (int i = 1; i < rows_count; i++) {
      y0 = *(matrix_v + i * 3 + 1);
      z0 = *(matrix_v + i * 3 + 2);
      *(matrix_v + i * 3 + 1) = cos(xd) * y0 - sin(xd) * z0;
      *(matrix_v + i * 3 + 2) = sin(xd) * y0 + cos(xd) * z0;
    }
  }
  if (fabs(0. - yd) > 1e-7) {
    // Поворот по оси Y
    for (int i = 1; i < rows_count; i++) {
      x0 = *(matrix_v + i * 3);
      z0 = *(matrix_v + i * 3 + 2);
      *(matrix_v + i * 3) = cos(yd) * x0 + sin(yd) * z0;
      *(matrix_v + i * 3 + 2) = cos(yd) * z0 - sin(yd) * x0;
    }
  }
  if (fabs(0. - zd) > 1e-7) {
    // Поворот по оси Z
    for (int i = 1; i < rows_count; i++) {
      x0 = *(matrix_v + i * 3);
      y0 = *(matrix_v + i * 3 + 1);
      *(matrix_v + i * 3) = cos(zd) * x0 - sin(zd) * y0;
      *(matrix_v + i * 3 + 1) = sin(zd) * x0 + cos(zd) * y0;
    }
  }
}

/* Масштабирование модели */
int scale(double *matrix_v, int rows_count, double k) {
  int error = 0;
  if (fabs(0. - k) > 1e-7) {
    for (int i = 1; i < rows_count; i++) {
      *(matrix_v + i * 3) *= k;
      *(matrix_v + i * 3 + 1) *= k;
      *(matrix_v + i * 3 + 2) *= k;
    }
  } else {
    error = 1;
  }
  return error;
}
