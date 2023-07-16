/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:22 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/cylinder.h"

object_t	*cylinder(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	object_t	*cylinder;

	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cy_int_test;
	return (cylinder);
}

int	cy_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	cep_t		cylinder_prop;
	ray_t		*bck_ray;
	t_vector	*poi;
	t_vector	n;
	int			index;

	cylinder_prop = ((cep_t){.t = (double[]){MAX_V, MAX_V, MAX_V, MAX_V},
		.valide_intersections = (int[]){FALSE, FALSE, FALSE, FALSE},
		.intersections = (t_vector *[]){NULL, NULL, NULL, NULL}});
	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	index = cylinder_intersection_points(bck_ray, prop, &cylinder_prop);
	delete_ray(bck_ray);
	if (index == -1)
		return (FALSE);
	poi = copy_vector(*cylinder_prop.intersections[index]);
	free_list((void **)cylinder_prop.intersections, 4);
	if (index < 2)
		return (set_cylider_properiesties(this, poi, prop));
	else
		return (set_cap_properiesties(this, poi, n, prop));
}

int	cylinder_intersection_points(ray_t *bck_ray, propretries_t *prop,
		cep_t *cylinder_prop)
{
	t_vector	p;
	t_vector	n;
	int			index;

	n = *bck_ray->m_lab;
	normalize(&n);
	p = *bck_ray->point1;
	calulcat_cylider_intersection(p, n, cylinder_prop);
	if (!close_enough(n.z, 0.0f))
		calulcat_cap_intersection(p, n, cylinder_prop);
	if (!includes(cylinder_prop->valide_intersections, 4, TRUE))
		return (-1);
	index = min_index(cylinder_prop->t, 4);
	if (index < 2)
		prop->uv_cords = (t_uv_cords){atan2(cylinder_prop->intersections[index]->x,
			cylinder_prop->intersections[index]->y),
			cylinder_prop->intersections[index]->z};
	else
		prop->uv_cords = (t_uv_cords){p.x + (cylinder_prop->t[index] * n.x), p.y
			+ ((cylinder_prop->t[index] * n.y))};
	return (index);
}

/**
 *
 * solve tot t;
 * t^2.a + t.b + p = 0;
 * a = (nx^2 + ny^2)
 * b = (2.px.nx + 2.py.ny)
 * c = (py^2 + px^2 - r^2)
 */
void	calulcat_cylider_intersection(t_vector p, t_vector n,
		cep_t *cylinder_prop)
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
		cylinder_prop->t[0] = (-b + numsqrt) / (2 * a);
		cylinder_prop->t[1] = (-b - numsqrt) / (2 * a);
		cylinder_prop->intersections[0] = ms_addition(&p, num_muliplication(&n,
				cylinder_prop->t[0]), 1);
		cylinder_prop->intersections[1] = ms_addition(&p, num_muliplication(&n,
				cylinder_prop->t[1]), 1);
		check_nd_set(cylinder_prop, 0,
			fabs(cylinder_prop->intersections[0]->z) < 1.0);
		check_nd_set(cylinder_prop, 1,
			fabs(cylinder_prop->intersections[1]->z) < 1.0);
	}
}

void	calulcat_cap_intersection(t_vector p, t_vector n, cep_t *cylinder_prop)
{
	cylinder_prop->t[2] = (p.z - 1) / -n.z;
	cylinder_prop->t[3] = (p.z + 1) / -n.z;
	cylinder_prop->intersections[2] = ms_addition(&p, num_muliplication(&n,
			cylinder_prop->t[2]), 1);
	cylinder_prop->intersections[3] = ms_addition(&p, num_muliplication(&n,
			cylinder_prop->t[3]), 1);
	if (cylinder_prop->t[2] > 0.0
		&& (sqrt(pow(cylinder_prop->intersections[2]->x, 2)
				+ pow(cylinder_prop->intersections[2]->y, 2))) < 1.0)
		cylinder_prop->valide_intersections[2] = TRUE;
	else
		cylinder_prop->t[2] = MAX_V;
	if (cylinder_prop->t[3] > 0.0
		&& sqrt(pow(cylinder_prop->intersections[3]->x, 2)
			+ pow(cylinder_prop->intersections[3]->y, 2)) < 1.0)
		cylinder_prop->valide_intersections[3] = TRUE;
	else
		cylinder_prop->t[3] = MAX_V;
}

int	set_cylider_properiesties(object_t *this, t_vector *poi,
		propretries_t *prop)
{
	t_vector	*normal_fp;
	t_vector	*m_normal;
	t_vector	*int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(poi->x, poi->y, 0.0);
	m_normal = get_norm(this, normal_fp);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	free_list((void *[]){normal_fp, m_normal, int_poi, poi}, 4);
	return (TRUE);
}

int	set_cap_properiesties(object_t *this, t_vector *poi, t_vector n,
		propretries_t *prop)
{
	t_vector	*normal_fp;
	t_vector	*m_normal;
	t_vector	*int_poi;

	if (sqrt(pow(poi->x, 2) + pow(poi->y, 2)) >= 1.0 || close_enough(0.0, n.z))
	{
		free(poi);
		return (FALSE);
	}
	int_poi = apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(0.0, 0.0, 0 + poi->z);
	m_normal = get_norm(this, normal_fp);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	free_list((void *[]){poi, normal_fp, int_poi, m_normal}, 4);
	return (TRUE);
}

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
