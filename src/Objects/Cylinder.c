#include "headers/triangle.h"
void delete_ray(ray_t *);
int min_index(double *list, int size)
{
	int i = 0;
	int index = 0;
	if (size < 0 || !list)
		return (0);
	double min = list[0];
	while (i < size)
	{
		if (min > list[i])
		{
			index = i;
			min = list[i];
		}
		i++;
	}
	return (index);
}

int includes(int *list, int size, int value)
{
	if (!list)
		return (-1);
	int i;
	i = 0;
	while (i < size)
	{
		if (list[i] == value)
			return (value);
		i++;
	}
	return (0);
}

/**
 *
 * solve tot t;
 * t^2.a + t.b + p = 0;
 * a = (nx^2 + ny^2)
 * b = (2.px.nx + 2.py.ny)
 * c = (py^2 + px^2 - r^2)
 */

void calulcat_cylider_intersection(double *t, vector_t p, vector_t n, vector_t **intersections, int *valide_intersections)
{
	double b;
	double a;
	double c;
	double numsqrt;

	a = (pow(n.x, 2) + pow(n.y, 2));
	b = 2 * ((p.x * n.x) + (p.y * n.y));
	c = (pow(p.x, 2) + pow(p.y, 2) - 1.0);
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);
		intersections[0] = addition(&p, num_muliplication(&n, t[0]));
		intersections[1] = addition(&p, num_muliplication(&n, t[1]));
		if (t[0] > 0 && fabs(intersections[0]->z) < 1.0)
			valide_intersections[0] = TRUE;
		else
			t[0] = MAX_V;
		if (t[1] > 0 && fabs(intersections[1]->z) < 1.0)
			valide_intersections[1] = TRUE;
		else
			t[1] = MAX_V;
	}
}

void calulcat_cap_intersection(double *t, vector_t p, vector_t n, vector_t **intersections, int *valide_intersections)
{
	t[2] = (p.z - 1) / -n.z;
	t[3] = (p.z + 1) / -n.z;

	intersections[2] = addition(&p, num_muliplication(&n, t[2]));
	intersections[3] = addition(&p, num_muliplication(&n, t[3]));

	if (t[2] > 0.0 &&
		(sqrt(pow(intersections[2]->x, 2) + pow(intersections[2]->y, 2))) < 1.0)
		valide_intersections[2] = TRUE;
	else
		t[2] = MAX_V;

	if (t[3] > 0.0 &&
		sqrt(pow(intersections[3]->x, 2) + pow(intersections[3]->y, 2)) < 1.0)
		valide_intersections[3] = TRUE;
	else
		t[3] = MAX_V;
}

vector_t *set_cylider_properiesties(object_t *this, vector_t *poi,
									vector_t *local_normal, vector_t *local_color)
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
	vector_t *gb_normal = Apply_transform_vector(normal_fp, FRWRD, this);
	m_normal = normalized_sub(gb_normal, global_origin);
	*local_normal = *m_normal;
	*local_color = *this->base_color;
	free_list((void *[]){(void *)origin, (void *)normal_fp, (void *)global_origin, (void *)m_normal}, 4);
	return (int_poi);
}

vector_t *set_cap_properiesties(object_t *this, vector_t *poi,
								vector_t *local_normal, vector_t *local_color)
{
	vector_t *origin;
	vector_t *normal_fp;
	vector_t *m_normal;
	vector_t *global_origin;
	vector_t *int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);

	origin = vector(0.0, 0.0, 0.0);
	normal_fp = vector(0.0, 0.0, 0 + poi->z);

	global_origin = Apply_transform_vector(origin, FRWRD, this);

	m_normal = normalized_sub(Apply_transform_vector(normal_fp, FRWRD, this), global_origin);

	*local_normal = *m_normal;
	*local_color = *this->base_color;
	// free_list((void *[]){(void *)origin, (void *)normal_fp, (void *)global_origin, (void *)m_normal}, 4);
	return (int_poi);
}

int cy_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
				vector_t *local_normal, vector_t *local_color)
{
	ray_t *bck_ray;
	vector_t *intersections[4];
	vector_t p;
	vector_t n;
	vector_t *poi;
	vector_t *int_poi;
	int index;
	double *t;
	int *valide_intersections;

	t = (double[]){MAX_V, MAX_V, MAX_V, MAX_V};
	valide_intersections = (int[]){FALSE, FALSE, FALSE, FALSE};
	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	p = *bck_ray->point1;
	calulcat_cylider_intersection(t, p, n, intersections, valide_intersections);
	if (!close_enough(n.z, 0.0f))
		calulcat_cap_intersection(t, p, n, intersections, valide_intersections);
	delete_ray(bck_ray);
	if (!includes(valide_intersections, 4, TRUE))
		return FALSE;
	index = min_index(t, 4);
	poi = intersections[index];
	// free_list((void **)intersections, 4);
	if (index < 2)
	{
		int_poi = set_cylider_properiesties(this, poi,
												local_normal, local_color);
		*int_point = *int_poi;
		free(int_poi);
		return TRUE;
	}
	if (index >= 2)
	{
		if (close_enough(0.0, n.z))
			return FALSE;
		if (sqrt(pow(poi->x, 2) + pow(poi->y, 2)) >= 1.0)
			return FALSE;
		int_poi = set_cap_properiesties(this, poi,
											local_normal, local_color);
		*int_point = *int_poi;
		free(int_poi);
		return TRUE;
	}
	return (FALSE);
}

object_t *cylinder(vector_t *translation, vector_t *rotation,
				   vector_t *scal, vector_t *color)
{
	object_t *cylinder;
	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cy_int_test;
	return (cylinder);
}
