#ifndef RT_CAMERA
#define RT_CAMERA
#include "../math_lib/headers/types.h"
#include "../math_lib/headers/vectormath.h"

typedef struct camera
{
    vector_t *position;
    vector_t *loockat;
    vector_t *up;
    vector_t *screen_u;
    vector_t *screen_v;
    vector_t *screen_center;
    double lenght;
    double horizontal_size;
    double aspect_ration;
} camera_t;

#endif