#include "../headers/types.h"

matrix_t *Set_transform(matrix_t *translation, matrix_t *rotation, matrix_t *scal);
matrix_t *Inverse(matrix_t *matrix)
{
}

int sh_int_test(ray_t camera_ray, vector_t *int_point, vector_t *local_normal, vector_t *local_color)
{
    return (0);
}

object_t *create_sphere(matrix_t *translation, matrix_t *rotation, matrix_t *scal, vector_t *color)
{
    object_t *shphere = (object_t *)malloc(sizeof(object_t));
    shphere->fwd_tfm = Set_transform(translation, rotation, scal);
    shphere->fwd_tfm = Inverse(shphere->fwd_tfm);
    shphere->test_inter = sh_int_test;

    return (shphere);
}
