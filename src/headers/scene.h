#ifndef SCENE_H
#define SCENE_H
#include "../Objects/headers/spher.h"
#include "../Objects/headers/plane.h"
#include "../Objects/headers/triangle.h"
#include "../Objects/headers/cylinder.h"
#include "../Objects/headers/Cone.h"
#include "../Lights/headers/pointlight.h"
#include "../lib/lib.h"
#include "../lib/math/headers/matrix.h"
#include "../lib/math/headers/vectormath.h"
#include "camera.h"
#include "image.h"
#include "types.h"

int cast_ray(ray_t *ray, scene_t *scene, vector_t *c_intersection_point,
			 void **c_object, vector_t *c_norm, vector_t *c_color);
#endif