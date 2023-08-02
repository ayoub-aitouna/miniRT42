/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:27 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/02 04:18:51 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/types.h"
#include "headers/spher.h"

void p_int_point_propreties(t_vector *poi, t_object *this,
							t_propretries *prop)
{
	t_vector *normal_fp;
	t_vector *m_normal;
	t_vector *int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(0.0, 0.0, -1.0);
	m_normal = get_norm(this, normal_fp);
	if (this->textures)
		m_normal = apply_bump_map_textures(this->textures, m_normal,
										   prop->uv_cords);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){int_poi, m_normal, normal_fp}, 3);
}
// 1.2 == 0.2
// 1.2 - 1;
// 5.2 == 0.2
double norm(double v)
{
	if (fabs(v) <= 1)
		return v;
	while (v > 1)
		v -= 1.f;
	while (v < -1)
		v += 1.f;
	return v;
}

/**
 *  calculat u and v;
 *  A = ray.p1;
 *  K = ray.m_lab normilazed
 *  u = Ax + tKz; & v = ay + tky; & t = kz/az;
 */
t_vector *p_calculat_int_point(t_ray *ray, t_vector k, t_propretries *prop,
							   int *status)
{
	t_vector a;
	double t;
	double u;
	double v;

	a = *ray->point1;
	*status = 1;
	if (close_enough(0.0, k.z))
		return (false(status));
	t = -1 * (ray->point1->z / k.z);
	if (t < 0.0)
		return (false(status));
	u = a.x + (t * k.x);
	v = a.y + (t * k.y);
	if (((fabs(u) >= 1.0 || fabs(v) >= 1.0)) && FALSE)
		return (false(status));
	else
	{
		prop->uv_cords = (t_uv_cords){.u = norm(u), .v = norm(v)};
		return (ms_addition(ray->point1, num_muliplication(&k, t), 1));
	}
}

int p_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_vector *poi;
	t_ray *bck_ray;
	t_vector vhat;
	int status;

	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	vhat = *bck_ray->m_lab;
	normalize(&vhat);
	poi = p_calculat_int_point(bck_ray, vhat, prop, &status);
	delete_ray(bck_ray);
	if (status == 0)
	{
		free(poi);
		return (FALSE);
	}
	p_int_point_propreties(poi, this, prop);
	free(poi);
	return (TRUE);
}

t_object *plane(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color)
{
	t_object *plane;

	plane = object_base(translation, rotation, scal, color);
	plane->test_inter = p_int_test;
	return (plane);
}
