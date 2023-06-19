#ifndef RT_CAMERA
#define RT_CAMERA
#include "../lib/math/headers/types.h"
#include "../lib/math/headers/vectormath.h"
#include "types.h"

camera_t *Camera();
void calculat_geometry(camera_t *camera);
ray_t *generate_ray(camera_t *camera, int screenX, int screenY);

#endif
