#ifndef M_TYPES_H
#define M_TYPES_H
#include <stdlib.h>
#include "../math_lib/headers/types.h"
#include "../lib/lib.h"

typedef int (*test_intersection)(struct ray, vector_t *, vector_t *, vector_t *);

typedef struct s_data
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_data;

typedef struct ray
{
	vector_t *point1;
	vector_t *point2;
	vector_t *m_lab;
} ray_t;

typedef struct Object
{
	matrex_t *fwd_tfm;
	matrex_t *bck_tfm;
	vector_t *base_color;
	test_intersection test_inter;
} object_t;

typedef struct Light
{
	vector_t *base_color;
	vector_t *position;
} light_t;

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

typedef struct Scene
{
	t_list *m_object_list;
	t_list *m_light_list;
	camera_t *m_camera;
} scene_t;
#endif
