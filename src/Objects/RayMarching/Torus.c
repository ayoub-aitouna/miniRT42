/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Torus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:42 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Torus.h"

object_t	*torus(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	object_t			*m_torus;
	t_rm_object_params	*torus_info;

	torus_info = malloc(sizeof(t_rm_object_params));
	*torus_info = (t_rm_object_params){torus_sdf, (t_vector){.7, .3, 0}};
	m_torus = rm_object(translation, rotation, scal, color);
	m_torus->extra = torus_info;
	m_torus->test_inter = torus_test_int;
	return (m_torus);
}

double	torus_sdf(t_vector p, t_vector params)
{
	t_vector	q;
	float		majorRadius;
	float		minorRadius;
	float		qxy;
	float		distance;
	t_vector	center;

	center = (t_vector){0, 0, 0};
	q = (t_vector){p.x - center.x, p.y - center.y, p.z - center.z};
	majorRadius = params.x;
	minorRadius = params.y;
	qxy = sqrtf((q.x * q.x) + (q.y * q.y)) - majorRadius;
	distance = sqrtf((qxy * qxy) + (q.z * q.z)) - minorRadius;
	return (distance);
}

int	torus_test_int(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	int valide;
	double u;
	double v;
	valide = rm_int_test(this, camera_ray, prop);
	if (valide)
	{
		u = atan2(prop->poi.y, prop->poi.x);
		v = (atan2(prop->poi.z, sqrt(pow(prop->poi.x, 2) + pow(prop->poi.y, 2))
				- ((t_rm_object_params *)this->extra)->params.x));
		if (v < 0)
			v += PI;
		u /= PI;
		v /= PI;
		prop->uv_cords = (t_uv_cords){u, v};
	}
	return (valide);
}