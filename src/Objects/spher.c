/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spher.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:30 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/07 22:24:52 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/spher.h"
#include <math.h>

object_t	*create_sphere(vector_t *translation, vector_t *rotation,
		vector_t *scal, vector_t *color)
{
	object_t	*shphere;

	shphere = object_base(translation, rotation, scal, color);
	shphere->test_inter = sh_int_test;
	return (shphere);
}

int	sh_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	vector_t	*poi;
	ray_t		*bck_ray;
	vector_t	vhat;
	int			status;

	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	vhat = *bck_ray->m_lab;
	normalize(&vhat);
	poi = calculat_int_point(bck_ray, vhat, &status);
	delete_ray(bck_ray);
	if (!status)
	{
		free(poi);
		return (FALSE);
	}
	int_point_propreties(poi, this, prop);
	free(poi);
	return (TRUE);
}

vector_t	*calculat_int_point(ray_t *bck_ray, vector_t vhat, int *status)
{
	double	b;
	double	c;
	double	thelta;
	double	t;

	*status = TRUE;
	b = 2 * dot(*bck_ray->point1, vhat);
	c = dot(*bck_ray->point1, *bck_ray->point1) - 1.0f;
	thelta = pow(b, 2) - (4 * c);
	t = min_t(sqrtf(thelta), b, status);
	if (thelta <= 0)
		return (false(status));
	if (*status == FALSE)
		return (NULL);
	return (fs_addition(bck_ray->point1, num_muliplication(&vhat, t)));
}

void	calculat_uv(propretries_t *prop, vector_t *poi)
{
	double	u;
	double	v;

	u = atan2(sqrt(poi->x * poi->x + poi->y * poi->y), poi->z);
	v = atan2(poi->y, poi->x);
	if (v < 0)
		v += PI;
	u /= PI;
	v /= PI;
	prop->uv_cords.u = u;
	prop->uv_cords.v = v;
}

void	int_point_propreties(vector_t *poi, object_t *this, propretries_t *prop)
{
	vector_t	*m_normal;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	calculat_uv(prop, poi);
	m_normal = get_norm(this, poi);
	// if (this->textures)
	// m_normal = apply_bump_map_textures(this->textures, m_normal,
	// prop->uv_cords);
	normalize(m_normal);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){int_poi, m_normal}, 2);
}

double	min_t(double numsqrt, double b, int *status)
{
	double	t1;
	double	t2;

	t1 = (-b + numsqrt) / 2.0;
	t2 = (-b - numsqrt) / 2.0;
	if (t1 < 0.0 && t2 < 0.0)
	{
		*status = FALSE;
		return (0);
	}
	if (t1 < t2)
	{
		if (t1 > .0)
			return (t1);
		else if (t2 > .0)
			return (t2);
		else
		{
			*status = FALSE;
			return (0);
		}
	}
	else
	{
		if (t2 > .0)
			return (t2);
		else if (t1 > .0)
			return (t1);
		else
		{
			*status = FALSE;
			return (0);
		}
	}
}

vector_t	*fs_addition(vector_t *u, vector_t *v)
{
	vector_t	*re;

	re = addition(u, v);
	free(v);
	return (re);
}
