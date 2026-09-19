#ifndef SIZE_VEC_H
#define SIZE_VEC_H

#include <stdbool.h>
#include <stddef.h>
typedef struct {
  size_t *data;
  size_t count;
  size_t capacity;
} SizeVec;

bool size_vec_push(SizeVec *v, size_t value);
void size_vec_free(SizeVec *v);

#endif // !SIZE_VEC_H
