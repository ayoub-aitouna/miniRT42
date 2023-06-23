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

/// @brief Delete Operator Overload
/// @param object_t *
void deleteObjectBase(object_t *this)
{
    if (this)
    {
        if (this->base_color)
            free(this->base_color);
        if (this->bck_tfm)
            free(this->bck_tfm);
        if (this->fwd_tfm)
            free(this->fwd_tfm);
        free(this);
    }
}