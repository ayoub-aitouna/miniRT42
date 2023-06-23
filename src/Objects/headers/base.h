#ifndef OBJECT_BASE_HPP
#define OBJECT_BASE_HPP
#include "../../headers/types.h"
#include "../../headers/types.h"
#include "../../headers/main.h"
#include "../../lib/math/headers/vectormath.h"
#include "../../lib/math/headers/matrix.h"

object_t *object_base(vector_t *translation, vector_t *rotation,
                      vector_t *scal, vector_t *color);
#endif