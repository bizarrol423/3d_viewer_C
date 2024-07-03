#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SIZESTR 2048

/* Полигоны в 1-мерном массиве */
typedef struct Facets {
  int *counts_vrtxs;  // массив количества вершин в полигонах
  int *vrtxs;
  int size_v;  // размер массива vrtxs
} facet_t;

/* Матрица вершин в 1-мерном массиве */
typedef struct Matrix {
  double *matrix, *origin;
  int rows;
  int cols;
  double xMin, xMax;
  double yMin, yMax;
  double zMin, zMax;
  double Max_lngth;
} matrix_t;

/* Инфа о вершинах и полигонах */
typedef struct Data {
  int count_of_vrtxs;
  int count_of_fcts;
  matrix_t matrix_3d;
  facet_t facet;
} model;

/* Создание и удаление модели */
int create_model(model *s, const char *filename);
void remove_model(model *s);

/* Аффинные преобразования */
void shift(double *matrix_v, int rows_count, double x, double y, double z);
void turn(double *matrix_v, int rows_count, double xd, double yd, double zd);
int scale(double *matrix_v, int rows_count, double k);

/* Вспомогательное */
int second_read(model *s, const char *filename);
int read_vrtx(model *s, char *strFile, int *vrtx);
void mem_alloc(model *s);
void create_facet(model *s);
void init_model(model *s);
int vrtxs_of_facets(char *strFile);
int rec_points(model *s, char *strFile, int fct);
void reset_matrix(model *s);
