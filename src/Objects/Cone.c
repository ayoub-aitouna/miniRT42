#include "headers/Cone.h"

void		delete_ray(ray_t *);

/**
 *
 * solve tot t;
 * t^2.a + t.b + p = 0;
 * a = (nx^2 + ny^2)
 * b = (2.px.nx + 2.py.ny)
 * c = (py^2 + px^2 - r^2)
 */

int	in_range(double value, double min, double max)
{
	return (value > min && value < max);
}

void	cone_cap_intersection(vector_t p, vector_t n, cep_t propretries)
{
	propretries.t[2] = (p.z - 1) / -n.z;
	propretries.intersections[2] = ms_addition(&p, num_muliplication(&n,
				propretries.t[2]), 1);
	if (propretries.t[2] > 0.0 &&
		(sqrt(pow(propretries.intersections[2]->x, 2)
					+ pow(propretries.intersections[2]->y, 2))) < 1.0)
		propretries.valide_intersections[2] = TRUE;
	else
		propretries.t[2] = MAX_V;
}

void	calulcat_cone_intersection(vector_t p, vector_t n, cep_t propretries)
{
	double	b;
	double	a;
	double	c;
	double	numsqrt;

	a = (pow(n.x, 2) + pow(n.y, 2) - pow(n.z, 2));
	b = 2 * ((p.x * n.x) + (p.y * n.y) - (p.z * n.z));
	c = (pow(p.x, 2) + pow(p.y, 2) - pow(p.z, 2));
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		propretries.t[0] = (-b + numsqrt) / (2 * a);
		propretries.t[1] = (-b - numsqrt) / (2 * a);
		propretries.intersections[0] = ms_addition(&p, num_muliplication(&n,
					propretries.t[0]), 1);
		propretries.intersections[1] = ms_addition(&p, num_muliplication(&n,
					propretries.t[1]), 1);
		if (propretries.t[0] > 0 && in_range(propretries.intersections[0]->z,
				.0, 1.))
			propretries.valide_intersections[0] = TRUE;
		else
			propretries.t[0] = MAX_V;
		if (propretries.t[1] > 0 && in_range(propretries.intersections[1]->z,
				.0, 1.))
			propretries.valide_intersections[1] = TRUE;
		else
			propretries.t[1] = MAX_V;
	}
	else
	{
		propretries.intersections[0] = NULL;
		propretries.intersections[1] = NULL;
	}
}

int	cone_int_test(object_t *this, ray_t *camera_ray, vector_t *int_point,
		vector_t *local_normal, vector_t *local_color)
{
	ray_t		*bck_ray;
	vector_t	*intersections[3];
	vector_t	p;
	vector_t	n;
	vector_t	*poi;
	vector_t	*int_poi;
	int			index;
	double		*t;
	int			*valide_intersections;

	t = (double[]){MAX_V, MAX_V, MAX_V};
	valide_intersections = (int[]){FALSE, FALSE, FALSE};
	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	p = *bck_ray->point1;
	calulcat_cone_intersection(p, n, (cep_t){.t = t,
			.intersections = intersections,
			.valide_intersections = valide_intersections});
	if (!close_enough(n.z, 0.0f))
		cone_cap_intersection(p, n, (cep_t){.t = t,
				.intersections = intersections,
				.valide_intersections = valide_intersections});
	else
		intersections[2] = NULL;
	delete_ray(bck_ray);
	if (!includes(valide_intersections, 3, TRUE))
	{
		free_list((void **)intersections, 3);
		return (FALSE);
	}
	index = min_index(t, 3);
	poi = copy_vector(*intersections[index]);
	free_list((void **)intersections, 3);
	if (index < 2)
	{
		int_poi = set_cylider_properiesties(this, poi, local_normal,
				local_color);
		*int_point = *int_poi;
		free(int_poi);
		free(poi);
		return (TRUE);
	}
	if (index >= 2)
	{
		if (sqrt(pow(poi->x, 2) + pow(poi->y, 2)) >= 1.0 || close_enough(0.0,
				n.z))
		{
			free(poi);
			return (FALSE);
		}
		int_poi = set_cap_properiesties(this, poi, local_normal, local_color);
		*int_point = *int_poi;
		free(int_poi);
		free(poi);
		return (TRUE);
	}
	return (FALSE);
}

object_t	*cone(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*cylinder;

	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cone_int_test;
	return (cylinder);
}
