#include <string.h>

#include "s_object.h"

/* Инициализация модели */
void init_model(model *s) {
  s->count_of_vrtxs = s->count_of_fcts = 0;
  s->matrix_3d.matrix = NULL;
  s->matrix_3d.origin = NULL;
  s->facet.counts_vrtxs = s->facet.vrtxs = NULL;
  s->matrix_3d.xMax = s->matrix_3d.xMin = NAN;
  s->matrix_3d.yMax = s->matrix_3d.yMin = NAN;
  s->matrix_3d.zMax = s->matrix_3d.zMin = NAN;
  s->matrix_3d.Max_lngth = 0;
  s->facet.size_v = 0;
}

/* Выделение памяти для модели */
void mem_alloc(model *s) {
  s->matrix_3d.rows = s->count_of_vrtxs + 1;
  s->matrix_3d.cols = 3;
  s->matrix_3d.matrix =
      (double *)malloc(s->matrix_3d.rows * 3 * sizeof(double));
  s->matrix_3d.origin =
      (double *)malloc(s->matrix_3d.rows * 3 * sizeof(double));
  s->facet.vrtxs = (int *)calloc(1, sizeof(int));
  s->facet.counts_vrtxs = (int *)calloc((s->count_of_fcts), sizeof(int));
}

/* Считывание из файла для записи данных о вершинах и полигонах  */
int second_read(model *s, const char *filename) {
  int error = 0;
  FILE *obj = NULL;
  obj = fopen(filename, "r");
  char strFile[SIZESTR] = "";
  if (obj) {
    int vrtx = 1, fct = 0;
    while (fgets(strFile, SIZESTR, obj) != NULL) {
      if (strFile[0] == 'v' && strFile[1] == ' ') {
        error = read_vrtx(s, strFile, &vrtx);
        if (error != 0) break;
        double xl = s->matrix_3d.xMax - s->matrix_3d.xMin;
        double yl = s->matrix_3d.yMax - s->matrix_3d.yMin;
        double zl = s->matrix_3d.zMax - s->matrix_3d.zMin;
        double tmp = (xl > yl) ? (xl > zl) ? xl : zl : (yl > zl) ? yl : zl;
        if (tmp > s->matrix_3d.Max_lngth) {
          s->matrix_3d.Max_lngth = tmp;
        }
      } else if (strFile[0] == 'f' && strFile[1] == ' ') {
        s->facet.counts_vrtxs[fct] = vrtxs_of_facets(strFile);
        if (s->facet.counts_vrtxs[fct] < 6) {
          error = 6;
          break;
        }
        s->facet.size_v += s->facet.counts_vrtxs[fct];
        create_facet(s);
        error = rec_points(s, strFile, fct++);
        if (error) {
          break;
        }
      }
    }
    fclose(obj);
  } else {
    error = 2;
  }
  return error;
}

/* Считывание строки с координатами вершины */
int read_vrtx(model *s, char *strFile, int *vrtx) {
  int error = 0;
  double crdnt = NAN;
  char *str = strtok(strFile + 1, " ");
  for (int i = 0; str != NULL; i++) {
    sscanf(str, "%lf", &crdnt);
    if (!i) {
      if (s->matrix_3d.xMax != s->matrix_3d.xMax && crdnt == crdnt) {
        s->matrix_3d.xMax = s->matrix_3d.xMin = crdnt;
      }
      if (crdnt > s->matrix_3d.xMax) {
        s->matrix_3d.xMax = crdnt;
      } else if (crdnt < s->matrix_3d.xMin) {
        s->matrix_3d.xMin = crdnt;
      }
      *(s->matrix_3d.matrix + *vrtx * 3) = crdnt;
      *(s->matrix_3d.origin + *vrtx * 3) = crdnt;
    } else if (i == 1) {
      if (s->matrix_3d.yMax != s->matrix_3d.yMax && crdnt == crdnt) {
        s->matrix_3d.yMax = s->matrix_3d.yMin = crdnt;
      }
      if (crdnt > s->matrix_3d.yMax) {
        s->matrix_3d.yMax = crdnt;
      } else if (crdnt < s->matrix_3d.yMin) {
        s->matrix_3d.yMin = crdnt;
      }
      *(s->matrix_3d.matrix + *vrtx * 3 + 1) = crdnt;
      *(s->matrix_3d.origin + *vrtx * 3 + 1) = crdnt;
    } else if (i == 2) {
      if (s->matrix_3d.zMax != s->matrix_3d.zMax && crdnt == crdnt) {
        s->matrix_3d.zMax = s->matrix_3d.zMin = crdnt;
      }
      if (crdnt > s->matrix_3d.zMax) {
        s->matrix_3d.zMax = crdnt;
      } else if (crdnt < s->matrix_3d.zMin) {
        s->matrix_3d.zMin = crdnt;
      }
      *(s->matrix_3d.origin + *vrtx * 3 + 2) = crdnt;
      *(s->matrix_3d.matrix + (*vrtx)++ * 3 + 2) = crdnt;
    } else {
      break;
    }
    str = strtok(NULL, " ");
  }
  if (crdnt != crdnt) {
    error = 1;
  }
  return error;
}

/* Подсчет количества вершин в полигоне */
int vrtxs_of_facets(char *strFile) {
  int vertexes = 0;
  char STR[SIZESTR] = "";
  strncpy(STR, strFile, SIZESTR);
  if (STR[strlen(STR) - 1] == '\n') {
    STR[strlen(STR) - 1] = ' ';
  }
  char *token = strtok(STR + 1, " ");
  while (token != NULL) {
    if (!strchr("\n", token[0])) {
      vertexes++;
    }
    token = strtok(NULL, " ");
  }
  return vertexes * 2;
}

/* Выделение памяти для полигона */
void create_facet(model *s) {
  s->facet.vrtxs =
      (int *)realloc(s->facet.vrtxs, s->facet.size_v * sizeof(int));
}

/* Запись вершин в полигон */
int rec_points(model *s, char *strFile, int fct) {
  int error = 0;
  char STR[SIZESTR] = "";
  strncpy(STR, strFile, SIZESTR);
  if (STR[strlen(STR) - 1] == '\n') {
    STR[strlen(STR) - 1] = ' ';
  }
  int point = 0, first_v = 0;  // номер вершины
  int curr =
      s->facet.size_v - s->facet.counts_vrtxs[fct];  // индекс текущего полигона
  int i = 0;
  char *token = strtok(STR + 1, " ");
  for (; i < s->facet.counts_vrtxs[fct]; i++) {
    if (token != NULL) {
      sscanf(token, "%d", &point);
      if (point < 1) {
        error = 5;
        break;
      }
      if (!strchr("\n", token[0])) {
        if (!i) {
          first_v = point;
          *(s->facet.vrtxs + curr + i) = first_v;
        } else {
          *(s->facet.vrtxs + curr + i) = point;
          *(s->facet.vrtxs + curr + ++i) = point;
        }
      }
      token = strtok(NULL, " ");
    } else if (i == s->facet.counts_vrtxs[fct] - 1) {
      *(s->facet.vrtxs + curr + i) = first_v;
      break;
    }
  }
  return error;
}

/* Сброс массива вершин к исходному */
void reset_matrix(model *s) {
  for (int i = 0; i < s->matrix_3d.rows; i++) {
    *(s->matrix_3d.matrix + i * 3) = *(s->matrix_3d.origin + i * 3);
    *(s->matrix_3d.matrix + i * 3 + 1) = *(s->matrix_3d.origin + i * 3 + 1);
    *(s->matrix_3d.matrix + i * 3 + 2) = *(s->matrix_3d.origin + i * 3 + 2);
  }
}
