/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:27 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 08:50:29 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/types.h"
#include "headers/spher.h"

void	p_int_point_propreties(vector_t *poi, object_t *this,
		propretries_t *prop)
{
	vector_t	*m_normal;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	m_normal = get_norm(this, poi);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){int_poi, m_normal}, 2);
}

/**
 *  calculat u and v;
 *  A = ray.p1;
 *  K = ray.m_lab normilazed
 *  u = Ax + tKz; & v = ay + tky; & t = kz/az;
 */
vector_t	*p_calculat_int_point(ray_t *ray, vector_t k, propretries_t *prop,
		int *status)
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
	if (fabs(u) >= 1.0 || fabs(v) >= 1.0)
		return (false(status));
	else
	{
		prop->uv_cords = (t_uv_cords){.u = u, .v = v};
		return (ms_addition(ray->point1, num_muliplication(&k, t), 1));
	}
}

int	p_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	vector_t	*poi;
	ray_t		*bck_ray;
	vector_t	vhat;
	int			status;

	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
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

object_t	*plane(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*plane;

	plane = object_base(translation, rotation, scal, color);
	plane->test_inter = p_int_test;
	plane->material->shininess_coefficient = 10;
	plane->material->reflection_coefficient = .6;
	return (plane);
}
