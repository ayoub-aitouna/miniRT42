
#include "headers/SimpleMaterial.h"
#include "headers/MaterialBase.h"
#include <stdlib.h>

material_t *new_simple_material(double shininess_coefficient, double reflection_coefficient)
{
    material_t *simple_material;
    simple_material = new_material_base(shininess_coefficient, reflection_coefficient);
    simple_material->calculat_color = calculat_color;
    return (simple_material);
}

vector_t *calculat_color(scene_t *scene, vector_t *localNormal,
                         vector_t *initPoint, vector_t *base_color, object_t *cur_object, ray_t *camera_ray)
{
    vector_t *color;
    vector_t *specularColor;
    specularColor = NULL;
    color = CalculatDiffuseColor(scene, localNormal,
                                 initPoint, base_color, cur_object);
    if (cur_object->material->shininess_coefficient > 0.f)
    {
        specularColor = Calculat_specularColor(scene, localNormal,
                                               initPoint, base_color, cur_object, camera_ray);
    }
    if (specularColor)
        color = addition(color, specularColor);
    return (color);
}

vector_t *Calculat_specularColor(scene_t *scene, vector_t *localNormal,
                                 vector_t *initPoint, vector_t *base_color, object_t *cur_object, ray_t *camera_ray)
{
    t_list *tmp;
    object_t *obj;
    light_t *light;
    vector_t local_norm;
    vector_t local_int;
    vector_t local_color;
    vector_t *light_dir;
    vector_t *specularColor;

    int valide_itersection;
    double specular_intensity;

    tmp = scene->m_light_list;
    specularColor = vector(0.f, 0.f, 0.f);

    while (tmp)
    {

        light = (light_t *)tmp->content;
        specular_intensity = 0;

        light_dir = normalized_sub(light->position, initPoint);

        vector_t *start_pos = addition(initPoint, num_muliplication(light_dir, 0.001));
        ray_t *lighit_ray = ray(start_pos, addition(start_pos, light_dir));

        valide_itersection = FALSE;
        t_list *object_tmp = scene->m_object_list;
        while (object_tmp)
        {
            obj = (object_t *)object_tmp->content;
            valide_itersection = obj->test_inter(obj, lighit_ray, &local_int, &local_norm, &local_color);
            if (valide_itersection)
                break;
            object_tmp = object_tmp->next;
        }
        if (!valide_itersection)
        {
            vector_t *reflection_vector = Reflection_vector(lighit_ray->m_lab, localNormal);
            vector_t *v = normalized(camera_ray->m_lab);
            double dotProduct = dot(*reflection_vector, *v);
            free_list((void *[]){v, reflection_vector}, 2);
            if (dotProduct > 0.0)
                specular_intensity = cur_object->material->reflection_coefficient * pow(dotProduct, cur_object->material->shininess_coefficient);
            specularColor->x += light->base_color->x * specular_intensity;
            specularColor->y += light->base_color->y * specular_intensity;
            specularColor->z += light->base_color->z * specular_intensity;
        }
        tmp = tmp->next;
    }
    return (specularColor);
}

vector_t *CalculatDiffuseColor(scene_t *scene, vector_t *localNormal,
                               vector_t *initPoint, vector_t *base_color, object_t *cur_object)
{
    vector_t Color;
    t_list *tmp;
    double intensity;
    int validIlum;
    double r;
    double g;
    double b;

    validIlum = 0;
    r = scene->ambient_light_factor.x;
    g = scene->ambient_light_factor.y;
    b = scene->ambient_light_factor.z;
    tmp = scene->m_light_list;
    while (tmp)
    {
        validIlum = calculatIlumination(tmp->content, localNormal, initPoint,
                                        &intensity, &Color, scene, cur_object);
        if (validIlum)
        {
            r += (Color.x * intensity);
            g += (Color.y * intensity);
            b += (Color.z * intensity);
        }
        tmp = tmp->next;
    }
    return (vector(r * base_color->x, g * base_color->y, b * base_color->z));
}
