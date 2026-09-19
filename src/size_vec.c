#include "size_vec.h"
#include <stdlib.h>

bool size_vec_push(SizeVec *v, size_t value) {
  if (v->count >= v->capacity) {
    size_t capacity = v->capacity == 0 ? 4 : v->capacity * 2;

    size_t *grow = realloc(v->data, sizeof v->data[0] * capacity);
    if (grow == NULL) {
      return false;
    }
    v->data = grow;
    v->capacity = capacity;
  }
  v->data[v->count++] = value;
  return true;
}

void size_vec_free(SizeVec *v) {
  free(v->data);
  v->data = NULL;
  v->count = 0;
  v->capacity = 0;
}
