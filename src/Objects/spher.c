#include "../headers/types.h"
#include "headers/spher.h"

int sh_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point, vector_t *local_normal, vector_t *local_color)
{
    ray_t *bck_ray = Apply_transform(camera_ray, this, 0);
    vector_t *vhat = bck_ray->m_lab;
    normalize(vhat);
    double b = 2 * dot(*bck_ray->point1, *vhat);
    double raduis = 1.0f;
    double c = dot(*bck_ray->point1, *bck_ray->point1) - sqrtf(raduis);
    double test = (b * b) - 4 * c;
    if (test <= 0)
        return 0;
    double numSqrt = sqrtf(test);
    double t1 = (-b + numSqrt) / 2.0f;
    double t2 = (-b - numSqrt) / 2.0f;
    if (t1 < 0.0 || t2 < 0.0)
        return 0;
    // vector_t *poi;
    // if (t1 < t2)
    //     poi = pluse(bck_ray->point1, num_muliplication(vhat, t1));
    // else
    //     poi = pluse(bck_ray->point1, num_muliplication(vhat, t2));
    return (1);
}

object_t *create_sphere(vector_t *translation, vector_t *rotation, vector_t *scal, vector_t *color)
{
    object_t *shphere = (object_t *)malloc(sizeof(object_t));
    shphere->fwd_tfm = Set_transform(translation, rotation, scal);
    shphere->bck_tfm = inverse(shphere->fwd_tfm);
    shphere->test_inter = sh_int_test;
    return (shphere);
}
