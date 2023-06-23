#include "headers/base.h"

object_t *object_base(vector_t *translation, vector_t *rotation,
                vector_t *scal, vector_t *color)
{
    object_t *object;

    object = (object_t *)malloc(sizeof(object_t));
    object->fwd_tfm = Set_transform(translation, rotation, scal);
    object->bck_tfm = inverse(object->fwd_tfm);
    object->base_color = color;
    free(rotation);
    free(translation);
    return (object);
}
