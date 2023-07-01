/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:22 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/30 00:46:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cylinder.h"

int	min_index(double *list, int size)
{
	int		i;
	int		index;
	double	min;

	i = 0;
	index = 0;
	if (size < 0 || !list)
		return (0);
	min = list[0];
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

int	includes(int *list, int size, int value)
{
	int	i;

	if (!list)
		return (-1);
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
void	calulcat_cylider_intersection(double *t, vector_t p, vector_t n,
		vector_t **intersections, int *valide_intersections)
{
	double	b;
	double	a;
	double	c;
	double	numsqrt;

	a = (pow(n.x, 2) + pow(n.y, 2));
	b = 2 * ((p.x * n.x) + (p.y * n.y));
	c = (pow(p.x, 2) + pow(p.y, 2) - 1.0);
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		t[0] = (-b + numsqrt) / (2 * a);
		t[1] = (-b - numsqrt) / (2 * a);
		intersections[0] = ms_addition(&p, num_muliplication(&n, t[0]), 1);
		intersections[1] = ms_addition(&p, num_muliplication(&n, t[1]), 1);
		if (t[0] > 0 && fabs(intersections[0]->z) < 1.0)
			valide_intersections[0] = TRUE;
		else
			t[0] = MAX_V;
		if (t[1] > 0 && fabs(intersections[1]->z) < 1.0)
			valide_intersections[1] = TRUE;
		else
			t[1] = MAX_V;
	}
	else
	{
		intersections[0] = NULL;
		intersections[1] = NULL;
	}
}

void	calulcat_cap_intersection(double *t, vector_t p, vector_t n,
		vector_t **intersections, int *valide_intersections)
{
	t[2] = (p.z - 1) / -n.z;
	t[3] = (p.z + 1) / -n.z;
	intersections[2] = ms_addition(&p, num_muliplication(&n, t[2]), 1);
	intersections[3] = ms_addition(&p, num_muliplication(&n, t[3]), 1);
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

vector_t	*set_cylider_properiesties(object_t *this, vector_t *poi,
		vector_t *local_normal, vector_t *local_color)
{
	vector_t	*normal_fp;
	vector_t	*m_normal;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(poi->x, poi->y, 0.0);
	m_normal = get_norm(this, normal_fp);
	*local_normal = *m_normal;
	*local_color = *this->base_color;
	free_list((void *[]){normal_fp, m_normal},
				2);
	return (int_poi);
}

vector_t	*set_cap_properiesties(object_t *this, vector_t *poi,
		propretries_t *prop)
{
	vector_t	*origin;
	vector_t	*normal_fp;
	vector_t	*m_normal;
	vector_t	*global_origin;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	origin = vector(0.0, 0.0, 0.0);
	normal_fp = vector(0.0, 0.0, 0 + poi->z);
	global_origin = Apply_transform_vector(origin, FRWRD, this);
	m_normal = ms_normalized_sub(Apply_transform_vector(normal_fp, FRWRD, this),
									global_origin,
									0);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){(void *)origin, (void *)normal_fp,
			(void *)global_origin, (void *)m_normal}, 4);
	return (int_poi);
}

int	cy_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	ray_t		*bck_ray;
	vector_t	*intersections[4];
	vector_t	p;
	vector_t	n;
	vector_t	*poi;
	vector_t	*int_poi;
	int			index;
	double		*t;
	int			*valide_intersections;

	t = (double[]){MAX_V, MAX_V, MAX_V, MAX_V};
	valide_intersections = (int[]){FALSE, FALSE, FALSE, FALSE};
	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	p = *bck_ray->point1;
	calulcat_cylider_intersection(t, p, n, intersections, valide_intersections);
	if (!close_enough(n.z, 0.0f))
		calulcat_cap_intersection(t, p, n, intersections, valide_intersections);
	else
	{
		intersections[2] = NULL;
		intersections[3] = NULL;
	}
	delete_ray(bck_ray);
	if (!includes(valide_intersections, 4, TRUE))
	{
		free_list((void **)intersections, 4);
		return (FALSE);
	}
	index = min_index(t, 4);
	poi = copy_vector(*intersections[index]);
	free_list((void **)intersections, 4);
	if (index < 2)
	{
		int_poi = set_cylider_properiesties(this, poi, &prop->local_normal,
				&prop->local_color);
		prop->int_point = *int_poi;
		free_list((void *[]){int_poi, poi}, 2);
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
		int_poi = set_cap_properiesties(this, poi, prop);
		prop->int_point = *int_poi;
		free_list((void *[]){int_poi, poi}, 2);
		return (TRUE);
	}
	return (FALSE);
}

object_t	*cylinder(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*cylinder;

	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cy_int_test;
	return (cylinder);
}
