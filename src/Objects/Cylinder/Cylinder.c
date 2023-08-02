/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:22 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/02 04:20:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cylinder.h"

t_object	*cylinder(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	t_object	*cylinder;

	cylinder = object_base(translation, rotation, scal, color);
	cylinder->test_inter = cy_int_test;
	return (cylinder);
}

int	cy_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_cep		cylinder_prop;
	t_ray		*bck_ray;
	t_vector	*poi;
	t_vector	n;
	int			index;

	cylinder_prop = (t_cep){.t = (double []){MAX_V, MAX_V, MAX_V, MAX_V},
		.valide_intersections = (int []){FALSE, FALSE, FALSE, FALSE},
		.intersections = (t_vector *[]){NULL, NULL, NULL, NULL}};
	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	index = cylinder_intersection_points(bck_ray, prop, &cylinder_prop);
	delete_ray(bck_ray);
	if (index == -1)
		return (free_list((void **)cylinder_prop.intersections, 4), FALSE);
	poi = copy_vector(*cylinder_prop.intersections[index]);
	free_list((void **)cylinder_prop.intersections, 4);
	if (index < 2)
		return (set_cylider_properiesties(this, poi, prop));
	else
		return (set_cap_properiesties(this, poi, n, prop));
}

int	cylinder_intersection_points(t_ray *bck_ray, t_propretries *prop,
		t_cep *cylinder_prop)
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
		prop->uv_cords = (t_uv_cords){atan2(cylinder_prop
				->intersections[index]->x,
				cylinder_prop->intersections[index]->y),
			cylinder_prop->intersections[index]->z};
	else
		prop->uv_cords = (t_uv_cords){p.x + (cylinder_prop->t[index] * n.x), p.y
			+ ((cylinder_prop->t[index] * n.y))};
	return (index);
}

int	set_cylider_properiesties(t_object *this, t_vector *poi,
		t_propretries *prop)
{
	t_vector	*normal_fp;
	t_vector	*m_normal;
	t_vector	*int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(poi->x, poi->y, 0.0);
	m_normal = get_norm(this, normal_fp);
	if (this->textures)
		m_normal = apply_bump_map_textures(this->textures, m_normal,
										   prop->uv_cords);
	normalize(m_normal);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	free_list((void *[]){normal_fp, m_normal, int_poi, poi}, 4);
	return (TRUE);
}

int	set_cap_properiesties(t_object *this, t_vector *poi, t_vector n,
		t_propretries *prop)
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
	normal_fp = vector(0.0, 0.0, 1.0);
	m_normal = get_norm(this, normal_fp);
	if (this->textures)
		m_normal = apply_bump_map_textures(this->textures, m_normal,
										   prop->uv_cords);
	normalize(m_normal);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	free_list((void *[]){poi, normal_fp, int_poi, m_normal}, 4);
	return (TRUE);
}
