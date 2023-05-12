#ifndef RT_TYPES
#define RT_TYPES
#include "math_lib/headers/types.h"
typedef struct ray
{
    vector_t point1;
    vector_t point2;
    vector_t m_lab;
} ray_t;

typedef int (*test_intersection)(struct ray, vector_t *, vector_t *, vector_t *);

typedef struct Object
{
    matrex_t *fwd_tfm;
    matrex_t *bck_tfm;
    vector_t *base_color;
    test_intersection test_inter;
} object_t;

#endif