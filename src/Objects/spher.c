#include "../headers/types.h"

matrex_t *Set_transform(matrex_t *translation, matrex_t *rotation, matrex_t *scal);
matrex_t *Inverse(matrex_t *matrex)
{

}

int sh_int_test(ray_t camera_ray, vector_t *int_point, vector_t *local_normal, vector_t *local_color)
{
    return (0);
}

object_t *create_sphere(matrex_t *translation, matrex_t *rotation, matrex_t *scal, vector_t *color)
{
    object_t *shphere = (object_t *)malloc(sizeof(object_t));
    shphere->fwd_tfm = Set_transform(translation, rotation, scal);
    shphere->fwd_tfm = Inverse(shphere->fwd_tfm);
    shphere->test_inter = sh_int_test;

    return (shphere);
}
