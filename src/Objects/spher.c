#include "headers/spher.h"

object_t *create_sphere(vector_t *translation, vector_t *rotation,
						vector_t *scal, vector_t *color)
{
	object_t *shphere;
	shphere = object_base(translation, rotation, scal, color);
	shphere->test_inter = sh_int_test;
	return (shphere);
}

int sh_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
				vector_t *local_normal, vector_t *local_color)
{
	vector_t *poi;
	ray_t *bck_ray;
	vector_t vhat;
	int status;

	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	vhat = *bck_ray->m_lab;
	normalize(&vhat);
	poi = calculat_int_point(bck_ray, vhat, &status);
	if (!status)
		return (FALSE);
	int_point_propreties(poi, this, int_point, local_normal, local_color);
	free(bck_ray);
	free(poi);
	return (TRUE);
}

vector_t *calculat_int_point(ray_t *bck_ray, vector_t vhat, int *status)
{
	double b;
	double c;
	double thelta;
	double t;

	*status = TRUE;
	b = 2 * dot(*bck_ray->point1, vhat);
	c = dot(*bck_ray->point1, *bck_ray->point1) - 1.0f;
	thelta = pow(b, 2) - (4 * c);
	t = min_t(sqrtf(thelta), b, status);
	if (thelta <= 0)
	{
		*status = FALSE;
		return (NULL);
	}
	if (*status == FALSE)
		return (NULL);
	return (fs_pluse(bck_ray->point1, num_muliplication(&vhat, t)));
}


void int_point_propreties(vector_t *poi, object_t *this,
						  vector_t *int_point, vector_t *local_normal, vector_t *local_color)
{
	vector_t *Origin;
	vector_t *newOrigin;
	vector_t *m_normal;
	vector_t *int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	Origin = vector(0.0, 0.0, 0.0);
	newOrigin = Apply_transform_vector(Origin, FRWRD, this);
	m_normal = minus(int_poi, newOrigin);
	normalize(m_normal);
	*int_point = *int_poi;
	*local_normal = *m_normal;
	*local_color = *this->base_color;
	free(int_poi);
	free(Origin);
	free(newOrigin);
	free(m_normal);
}

double min_t(double numsqrt, double b, int *status)
{
	double t1;
	double t2;

	t1 = (-b + numsqrt) / 2.0;
	t2 = (-b - numsqrt) / 2.0;
	if (t1 < 0.0 || t2 < 0.0)
	{
		*status = FALSE;
		return (0);
	}
	if (t1 < t2)
		return (t1);
	return (t2);
}

vector_t *fs_pluse(vector_t *u, vector_t *v)
{
	vector_t *re;

	re = pluse(u, v);
	free(v);
	return (re);
}
