#include "headers/triangle.h"

int close_enough(double v1, double v2);

void cy_int_point_propreties(vector_t *poi, object_t *this,
		vector_t *int_point, vector_t *local_normal,
		vector_t *local_color)
{
	vector_t *origin;
	vector_t *normal_fp;
	vector_t *global_origin;
	vector_t *m_normal;
	vector_t *int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);

	origin = vector(0.0, 0.0, 0.0);
	global_origin = Apply_transform_vector(origin, FRWRD, this);

	normal_fp = vector(poi->x, poi->y, 0.0);

	m_normal = minus(Apply_transform_vector(normal_fp, FRWRD, this), global_origin);
	normalize(m_normal);

	*int_point = *int_poi;
	*local_normal = *m_normal;
	*local_color = *this->base_color;

}

int all_true(int *list, int size)
{
	int i = 0;
	int valide = FALSE;
	while (i < size)
	{
		if (list[i] == TRUE)
			valide = TRUE;
		i++;
	}
	return (valide);
}

/**
 *
 * solve tot t;
 * t^2.a + t.b + p = 0;
 * a = (nx^2 + ny^2)
 * b = (2.px.nx + 2.py.ny)
 * c = (py^2 + px^2 - r^2)
 */
vector_t *cy_calculat_int_point(ray_t *ray, vector_t n, int *status)
{
	double		t[4] = {MAX_V, MAX_V, MAX_V, MAX_V};
	int			valide_intersections[4] = {FALSE, FALSE, FALSE, FALSE};
	vector_t	*intersections[4];
	vector_t	p;
	double		b;
	double		a;
	double		c;
	int			i;
	int			min_value;
	int			min_i;
	double		numsqrt;

	min_value	= 10e6;
	min_i		= 0;
	i			= 0;
	p			= *ray->point1;
	a			= (pow(n.x, 2) + pow(n.y, 2));
	b			= 2 * ((p.x * n.x) + (p.y * n.y));
	c			= (pow(p.x, 2) + pow(p.y, 2) - 1);
	numsqrt		= sqrtf(pow(b, 2) - (4 * a * c));
	if (numsqrt > 0)
	{
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);

		intersections[0] = pluse(&p, num_muliplication(&n, t[0]));
		intersections[1] = pluse(&p, num_muliplication(&n, t[1]));

		if (t[0] > 0 && fabs(intersections[0]->z) < 1.0)
			valide_intersections[0] = TRUE;
		else
			t[0] = MAX_V;

		if (t[1] > 0 && fabs(intersections[1]->z) < 1.0)
			valide_intersections[1] = TRUE;
		else
			t[1] = MAX_V;
	}

	if (!close_enough(0.0, n.z))
	{
		t[2] = ((p.z - 1) / -n.z);
		t[3] = ((p.z + 1) / -n.z);

		intersections[2] = pluse(&p, num_muliplication(&n, t[2]));
		intersections[3] = pluse(&p, num_muliplication(&n, t[3]));

		if (t[2] > 0 && sqrtf(pow(intersections[2]->x, 2) + pow(intersections[2]->y, 2)) < 1.0)
			valide_intersections[2] = TRUE;
		else
			t[2] = MAX_V;

		if (t[3] > 0 && sqrtf(pow(intersections[3]->x, 2) + pow(intersections[3]->y, 2)) < 1.0)
			valide_intersections[3] = TRUE;
		else
			t[3] = MAX_V;
	}

	if (!all_true(valide_intersections, 4))
		return false(status);

	while (i < 4)
	{
		if (min_value > t[i])
		{
			min_value = t[i];
			min_i = i;
		}
		i++;
	}

	if (close_enough(0.0, n.z) && min_i >= 2)
		return (false(status));
	if (sqrtf(pow(intersections[min_i]->x, 2) + pow(intersections[min_i]->y, 2)) >= 1.0 && min_i >= 2)
		return (false(status));
	if (min_i < 2)
		*status = 1;
	else
		*status = 2;
	return intersections[min_i];
}

void cap_int_point_propreties(vector_t *poi, object_t *this,
		vector_t *int_point, vector_t *local_normal,
		vector_t *local_color)
{
	vector_t *origin;
	vector_t *normal_fp;
	vector_t *global_origin;
	vector_t *int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);

	origin = vector(0.0, 0.0, 0.0);
	normal_fp = vector(0.0, 0.0, 0 + poi->z);

	global_origin = Apply_transform_vector(origin, FRWRD, this);

	local_normal = minus(Apply_transform_vector(normal_fp, FRWRD, this), global_origin);
	normalize(local_normal);

	*int_point = *int_poi;
	*local_color = *this->base_color;
	free(int_poi);
	// print_vector(*local_normal);
}

int cy_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
		vector_t *local_normal, vector_t *local_color)
{
	vector_t *poi;
	ray_t *bck_ray;
	vector_t vhat;
	int status;
	bck_ray = Apply_transform(camera_ray, this, BCKWRD);

	vhat = *bck_ray->m_lab;
	normalize(&vhat);

	poi = cy_calculat_int_point(bck_ray, vhat, &status);
	if (status == FALSE)
		return (FALSE);
	if (status == 1)
		cy_int_point_propreties(poi, this, int_point, local_normal, local_color);
	else
		cap_int_point_propreties(poi, this, int_point, local_normal, local_color);
	free(bck_ray);
	free(poi);
	return (TRUE);
}

object_t *cylinder(vector_t *translation, vector_t *rotation,
		vector_t *scal, vector_t *color)
{
	object_t *cylinder;
	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cy_int_test;
	return (cylinder);
}
