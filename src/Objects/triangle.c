/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:36 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/02 04:18:58 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/triangle.h"

void	t_int_point_propreties(t_vector *poi, t_object *this,
		t_propretries *prop)
{
	t_vector	*m_normal;
	t_vector	*int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	m_normal = get_norm(this, int_poi);
	if (this->textures)
		m_normal = apply_bump_map_textures(this->textures, m_normal,
										   prop->uv_cords);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){m_normal, int_poi}, 2);
}

/**
 *  calculat u and v;
 *  A = ray.p1;
 *  K = ray.m_lab normilazed
 *  u = Ax + tKz; & v = ay + tky; & t = kz/az;
 */
t_vector	*t_calculat_int_point(t_ray *ray, t_vector k, int *status)
{
	t_vector	a;
	double		t;
	double		u;
	double		v;

	a = *ray->point1;
	*status = 1;
	if (close_enough(0.0, k.z))
		return (false(status));
	t = -1 * (ray->point1->z / k.z);
	if (t < 0.0)
		return (false(status));
	u = a.x + (t * k.x);
	v = a.y + (t * k.y);
	if (u < .0 || v < .0 || (u + v) > 1)
		return (false(status));
	else
		return (ms_addition(ray->point1, num_muliplication(&k, t), 1));
}

int	t_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_vector	*poi;
	t_ray		*bck_ray;
	t_vector	vhat;
	int			status;

	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	vhat = *bck_ray->m_lab;
	normalize(&vhat);
	poi = t_calculat_int_point(bck_ray, vhat, &status);
	delete_ray(bck_ray);
	if (status == 0)
	{
		free(poi);
		return (FALSE);
	}
	t_int_point_propreties(poi, this, prop);
	free(poi);
	return (TRUE);
}

t_object	*triangle(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	t_object	*triangle;

	triangle = object_base(translation, rotation, scal, color);
	triangle->test_inter = t_int_test;
	return (triangle);
}
