#ifndef RT_CAMERA
#define RT_CAMERA
#include "../lib/math/headers/types.h"
#include "../lib/math/headers/vectormath.h"
#include "types.h"
#include "ray.h"

camera_t *Camera(double horizontal_size, double lenght, double aspect_ration);
void Setloockat(camera_t *this, vector_t *loockat);
void SetUp(camera_t *this, vector_t *Up);
void SetPosition(camera_t *this, vector_t *position);
void calculat_geometry(camera_t *this);
ray_t *generate_ray(camera_t *this, double screenX, double screenY);

#endif
