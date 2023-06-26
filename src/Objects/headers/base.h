#ifndef OBJECT_BASE_HPP
#define OBJECT_BASE_HPP
#include "../../headers/types.h"
#include "../../headers/ray.h"
#include "../../headers/main.h"
#include "../../lib/math/headers/vectormath.h"
#include "../../lib/math/headers/matrix.h"

vector_t * false(int *status);
int close_enough(double v1, double v2);
object_t *object_base(vector_t *translation, vector_t *rotation,
                      vector_t *scal, vector_t *color);
void deleteObjectBase(object_t *this);
void delete_object_list(t_list *list);
#endif