#ifndef SIMPLEMATERIAL_H
#define SIMPLEMATERIAL_H
#include "../../headers/types.h"
#include "../../headers/main.h"
#include "../../lib/math/headers/vectormath.h"
#include "../../lib/math/headers/matrix.h"
material_t *new_simple_material(double shininess_coefficient, double reflection_coefficient);
vector_t *calculat_color(scene_t *scene, vector_t *localNormal,
                         vector_t *initPoint, vector_t *base_color, object_t *cur_object, ray_t *camera_ray);
vector_t *Calculat_specularColor(scene_t *scene, vector_t *localNormal,
                                 vector_t *initPoint, vector_t *base_color, object_t *cur_object, ray_t *camera_ray);
vector_t *CalculatDiffuseColor(scene_t *scene, vector_t *localNormal,
                               vector_t *initPoint, vector_t *base_color, object_t *cur_object);
#endif
