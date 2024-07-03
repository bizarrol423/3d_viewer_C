#include "s_object.h"

#include <string.h>

/* Начало считывания обж файла */
int create_model(model *s, const char *filename) {
  int error = 0;
  init_model(s);
  FILE *obj = NULL;
  obj = fopen(filename, "r");
  if (obj) {
    char *extension = strstr(filename, ".obj");
    if (extension && !strcmp(extension, ".obj")) {
      char strFile[SIZESTR] = "";
      while (fgets(strFile, SIZESTR, obj) != NULL) {
        if (strFile[0] == 'v' && strFile[1] == ' ') {
          s->count_of_vrtxs++;
        } else if (strFile[0] == 'f' && strFile[1] == ' ') {
          s->count_of_fcts++;
        }
      }
      if (s->count_of_fcts * s->count_of_vrtxs != 0) {
        mem_alloc(s);
        error = second_read(s, filename);
      } else {
        error = 3;
      }
    } else {
      error = 4;
    }
    fclose(obj);
  } else {
    error = 2;
  }
  return error;
}

/* Удаление модели */
void remove_model(model *s) {
  if (s->count_of_fcts && s->count_of_vrtxs) {
    if (s->matrix_3d.matrix) {
      free(s->matrix_3d.matrix);
    }
    if (s->matrix_3d.origin) {
      free(s->matrix_3d.origin);
    }
    if (s->facet.counts_vrtxs) {
      free(s->facet.counts_vrtxs);
    }
    if (s->facet.vrtxs) {
      free(s->facet.vrtxs);
    }
  }
  init_model(s);
}
