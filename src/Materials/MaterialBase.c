#include "headers/MaterialBase.h"

material_t *new_material_base(double shininess_coefficient, double reflection_coefficient)
{
    material_t *material_base;

    material_base = malloc(sizeof(material_t));
    material_base->reflection_coefficient = reflection_coefficient;
    material_base->shininess_coefficient = shininess_coefficient;

    return (material_base);
}
