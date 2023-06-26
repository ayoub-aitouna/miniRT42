#ifndef MATERIALBASE_H
#define MATERIALBASE_H
#include "../../headers/types.h"
#include "../../headers/main.h"
#include "../../headers/ray.h"
#include "../../lib/math/headers/vectormath.h"
#include "../../lib/math/headers/matrix.h"
#include "../../Lights/headers/pointlight.h"
material_t *new_material_base(double shininess_coefficient, double reflection_coefficient);
#endif
