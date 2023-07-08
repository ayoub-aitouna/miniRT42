#include "headers/Torus.h"

object_t	*torus(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t			*m_torus;
	t_rm_object_params	*torus_info;

	torus_info = malloc(sizeof(t_rm_object_params));
	*torus_info = (t_rm_object_params){torus_sdf, (vector_t){.7, .3, 0}};
	m_torus = rm_object(translation, rotation, scal, color);
	m_torus->extra = torus_info;
	m_torus->test_inter = torus_test_int;
	return (m_torus);
}

double	torus_sdf(vector_t p, vector_t params)
{
	vector_t	q;
	float		majorRadius;
	float		minorRadius;
	float		qxy;
	float		distance;
	vector_t	center;

	center = (vector_t){0, 0, 0};
	q = (vector_t){p.x - center.x, p.y - center.y, p.z - center.z};
	majorRadius = params.x;
	minorRadius = params.y;
	qxy = sqrtf((q.x * q.x) + (q.y * q.y)) - majorRadius;
	distance = sqrtf((qxy * qxy) + (q.z * q.z)) - minorRadius;
	return (distance);
}

int	torus_test_int(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	int valide;
	double u;
	double v;
	valide = rm_int_test(this, camera_ray, prop);
	if (valide)
	{
		u = atan2(prop->poi.y, prop->poi.x);
		v = (atan2(prop->poi.z, sqrt(pow(prop->poi.x, 2) + pow(prop->poi.y, 2))
					- ((t_rm_object_params *)this->extra)->params.x));
		if (v < 0)
			v += PI;
		u /= PI;
		v /= PI;
		prop->uv_cords = (t_uv_cords){u, v};
	}
	return (valide);
}