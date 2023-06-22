#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "../../headers/types.h"
#include "../../lib/math/headers/vectormath.h"
light_t *new_light(vector_t *position, vector_t *color, double intensity);
int	calculatIlumination(light_t *this, vector_t *localNormal,
		vector_t *initPoint, double *intensity, vector_t *Color, scene_t *scene, object_t* cur_Object);

#endif
