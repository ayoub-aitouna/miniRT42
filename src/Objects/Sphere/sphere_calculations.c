/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:15:22 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:15:55 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/spher.h"

t_vector	*calculat_int_point(t_ray *bck_ray, t_vector vhat, int *status)
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

void	calculat_uv(t_propretries *prop, t_vector *poi)
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

double	min_t(double numsqrt, double b, int *status)
{
	double	t1;
	double	t2;

	t1 = (-b + numsqrt) / 2.0;
	t2 = (-b - numsqrt) / 2.0;
	if (t1 < 0.0 && t2 < 0.0)
		return (*(status) = 0, 0);
	if (t1 < t2)
	{
		if (t1 > .0)
			return (t1);
		else if (t2 > .0)
			return (t2);
		else
			return (*(status) = 0, 0);
	}
	else
	{
		if (t2 > .0)
			return (t2);
		else if (t1 > .0)
			return (t1);
		else
			return (*(status) = 0, 0);
	}
}

t_vector	*fs_addition(t_vector *u, t_vector *v)
{
	t_vector	*re;

	re = addition(u, v);
	free(v);
	return (re);
}
