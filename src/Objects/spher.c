#include "../headers/types.h"
#include "headers/spher.h"

int sh_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
				vector_t *local_normal, vector_t *local_color)
{
	vector_t *poi;
	vector_t *int_poi;
	ray_t *bck_ray;
	vector_t *vhat;
	double b;
	double raduis;
	double c;
	double thelta;
	double numSqrt;
	double t1;
	double t2;

	bck_ray = Apply_transform(camera_ray, this, 0);
	vhat = bck_ray->m_lab;
	normalize(vhat);
	b = 2 * dot(*bck_ray->point1, *vhat);
	raduis = 1.0f;
	c = dot(*bck_ray->point1, *bck_ray->point1) - sqrtf(raduis);
	thelta = pow(b, 2) - 4 * c;
	if (thelta <= 0)
		return (0);
	numSqrt = sqrtf(thelta);
	t1 = (-b + numSqrt) / 2.0;
	t2 = (-b - numSqrt) / 2.0;
	if (t1 < 0.0 || t2 < 0.0)
		return (0);
	// TODO: calculat the intersection point localNormal
	if (t1 < t2)
		poi = pluse(bck_ray->point1, num_muliplication(vhat, t1));
	else
		poi = pluse(bck_ray->point1, num_muliplication(vhat, t2));

	int_poi = Apply_transform_vector(poi, 1, this);
	*int_point =  *int_poi;
	vector_t *Origin = vector(0.0,0.0,0.0);
	vector_t *newOrigin = Apply_transform_vector(Origin, 1, this);
	vector_t *m_normal = minus(int_point, newOrigin);
	normalize(m_normal);
	*local_normal = *m_normal;
	*local_color = *this->base_color;
	// free(m_normal);
	// free(local_color);
	// free(int_poi);
	return (1);
}


object_t *create_sphere(vector_t *translation, vector_t *rotation,
						vector_t *scal, vector_t *color)
{
	object_t *shphere;

	shphere = (object_t *)malloc(sizeof(object_t));
	shphere->fwd_tfm = Set_transform(translation, rotation, scal);
	shphere->bck_tfm = inverse(shphere->fwd_tfm);
	shphere->test_inter = sh_int_test;
	shphere->base_color = vector(.9, .5, .2);
	return (shphere);
}
