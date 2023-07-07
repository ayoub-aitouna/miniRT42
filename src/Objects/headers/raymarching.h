#ifndef RAYMARCHING_H
# define RAYMARCHING_H

# include "base.h"

# define MAX_STEPS 100

# ifndef M_EPSILON
#  define M_EPSILON 0.001
# endif
# ifndef D_S
#  define D_S 0.001
# endif

object_t	*rm_object(vector_t *translation, vector_t *rotation,
				vector_t *scal, vector_t *color);
int			rm_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
double		SDF(vector_t p, vector_t params);
double		calculat_sdf_diff(vector_t *normal, vector_t displacemnt,
				vector_t parms);
vector_t	get_local_normal(object_t *this, vector_t *cur_location,
				vector_t *dir_v, vector_t *params);
vector_t	*get_locatione_at_intersection(ray_t *bckray, vector_t *params,
				vector_t *dir_v);
#endif