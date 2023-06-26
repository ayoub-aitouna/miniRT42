#include "headers/base.h"
material_t *new_simple_material(double shininess_coefficient, double reflection_coefficient);
object_t *object_base(vector_t *translation, vector_t *rotation,
                      vector_t *scal, vector_t *color)
{
    object_t *object;

    object = (object_t *)malloc(sizeof(object_t));
    object->fwd_tfm = Set_transform(translation, rotation, scal);
    object->bck_tfm = inverse(object->fwd_tfm);
    object->base_color = color;
    object->material = new_simple_material(0.6, 2);
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

int close_enough(double v1, double v2)
{
    return (fabs(v1 - v2) < EPSILON);
}

vector_t * false(int *status)
{
    *status = FALSE;
    return (NULL);
}

/// @brief Delete[] Operator Overload
/// @param object_t *
void delete_object_list(t_list *list)
{
    while (list)
    {
        printf("deleting object %p \n", list);
        deleteObjectBase(list->content);
        free(list);
        list = list->next;
    }
}