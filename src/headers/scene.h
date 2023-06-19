#ifndef SCENE_H
#define SCENE_H
#include "types.h"
#include "../lib/lib.h"
#include "../Objects/headers/spher.h"
#include "../lib/math/headers/vectormath.h"
#include "../lib/math/headers/matrix.h"
#include "camera.h"
#include "image.h"
int cast_ray(ray_t *ray, scene_t *scene);
#endif