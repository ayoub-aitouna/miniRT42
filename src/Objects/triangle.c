/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:36 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:23:36 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/triangle.h"

void	t_int_point_propreties(vector_t *poi, object_t *this,
		propretries_t *prop)
{
	vector_t	*origin;
	vector_t	*normal_fp;
	vector_t	*global_origin;
	vector_t	*m_normal;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	origin = vector(0.0, 0.0, 0.0);
	normal_fp = vector(0.0, 0.0, -1.0);
	global_origin = Apply_transform_vector(origin, FRWRD, this);
	m_normal = ms_minus(Apply_transform_vector(normal_fp, FRWRD, this),
						global_origin,
						0);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){origin, normal_fp, global_origin, m_normal, int_poi},
				5);
}

/**
 *  calculat u and v;
 *  A = ray.p1;
 *  K = ray.m_lab normilazed
 *  u = Ax + tKz; & v = ay + tky; & t = kz/az;
 */
vector_t	*t_calculat_int_point(ray_t *ray, vector_t k, int *status)
{
	vector_t	a;
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

int	t_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	vector_t	*poi;
	ray_t		*bck_ray;
	vector_t	vhat;
	int			status;

	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
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

object_t	*triangle(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*triangle;

	triangle = object_base(translation, rotation, scal, color);
	triangle->test_inter = t_int_test;
	return (triangle);
}
