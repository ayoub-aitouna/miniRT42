#ifndef RT_CAMERA
#define RT_CAMERA
#include "../math_lib/headers/types.h"
#include "../math_lib/headers/vectormath.h"
#include "types.h"

camera_t *Camera();
void calculat_geometry(camera_t *camera);
ray_t *generate_ray(camera_t *camera, int screenX, int screenY);

#endif
