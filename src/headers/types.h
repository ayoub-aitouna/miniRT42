#ifndef M_TYPES_H
#define M_TYPES_H
#include <stdlib.h>
#include "../math_lib/headers/types.h"

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

typedef int (*test_intersection)(struct ray, vector_t *, vector_t *, vector_t *);

typedef struct Object
{
	matrex_t *fwd_tfm;
	matrex_t *bck_tfm;
	vector_t *base_color;
	test_intersection test_inter;
} object_t;

#endif