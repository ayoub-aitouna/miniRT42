#include "headers/MaterialBase.h"

material_t *new_material_base(double shininess_coefficient, double reflection_coefficient)
{
    material_t *material_base;

    material_base = malloc(sizeof(material_t));
    material_base->reflection_coefficient = reflection_coefficient;
    material_base->shininess_coefficient = shininess_coefficient;

    return (material_base);
}


vector_t *reflect_color(scene_t *scene, vector_t *localNormal,
		vector_t *initPoint, object_t *cur_object, ray_t *camera_ray)
{
    vector_t *reflection_v = Reflection_vector(camera_ray->m_lab, localNormal);
    // ray_t m_ray = ray(initPoint);
}

void delete_material(material_t *this)
{
    if (this)
        free(this);
}
