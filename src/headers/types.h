#ifndef M_TYPES_H
#define M_TYPES_H
#include <stdlib.h>
#include "../lib/lib.h"

typedef struct Object object_t;
typedef struct material material_t;

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

typedef int (*test_intersection)(object_t *this, struct ray *ray, vector_t *ip, vector_t *normal, vector_t *color);

typedef struct Object
{
	matrix_t *fwd_tfm;
	matrix_t *bck_tfm;
	vector_t *base_color;
	test_intersection test_inter;
	material_t *material;

} object_t;

typedef struct Light
{
	vector_t *base_color;
	vector_t *position;
	double m_intensity;
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
	vector_t ambient_light_factor;
} scene_t;

typedef struct Propretries
{
	vector_t local_color;
	vector_t local_normal;
	vector_t int_point;
} propretries_t;

typedef struct cylinder_equations_Propretries
{
	vector_t **intersections;
	int *valide_intersections;
	double *t;
} cep_t;

typedef vector_t *(*compute_color)(scene_t *scene, vector_t *localNormal,
								   vector_t *initPoint, vector_t *base_color, object_t *cur_object, ray_t *camera_ray);

typedef struct material
{
	double shininess_coefficient;
	double reflection_coefficient;
	compute_color calculat_color;

} material_t;

#endif
