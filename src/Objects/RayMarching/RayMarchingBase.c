/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayMarchingBase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:51 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/RayMarchingBase.h"

t_object	*rm_object(t_vector *translation, t_vector *rotation,
		t_vector *scal, t_vector *color)
{
	t_object	*rm_base_object;

	rm_base_object = object_base(translation, rotation, scal, color);
	rm_base_object->test_inter = rm_int_test;
	return (rm_base_object);
}

int	rm_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_ray		*bckray;
	t_vector	*dir_v;
	t_vector	*int_poi;
	t_vector	*cur_location;

	bckray = apply_transform(camera_ray, this, BCKWRD);
	dir_v = normilized_copy(bckray->m_lab);
	cur_location = get_locatione_at_intersection(this, bckray,
		&(((t_rm_object_params *)this->extra)->params), dir_v);
	if (!cur_location)
	{
		free_list((void *[]){cur_location, dir_v}, 2);
		return (FALSE);
	}
	int_poi = apply_transform_vector(cur_location, FRWRD, this);
	prop->local_normal = get_local_normal(this, cur_location, dir_v,
		&(((t_rm_object_params *)this->extra)->params));
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	prop->poi = *cur_location;
	free_list((void *[]){cur_location, dir_v, int_poi}, 3);
	delete_ray(bckray);
	return (TRUE);
}

t_vector	get_local_normal(t_object *this, t_vector *cur_location,
		t_vector *dir_v, t_vector *params)
{
	t_vector	*normalLoc;
	t_vector	normal;
	t_vector	*m_normal;
	t_vector	result;

	normalLoc = ms_minus(cur_location, num_muliplication(dir_v, 0.01), 1);
	normal = (t_vector){calculat_sdf_diff(this, normalLoc, (t_vector){D_S, 0.0,
		0.0}, *params), calculat_sdf_diff(this, normalLoc, (t_vector){0.0, D_S,
		0.0}, *params), calculat_sdf_diff(this, normalLoc, (t_vector){0.0, 0.0,
		D_S}, *params)};
	normalize(&normal);
	m_normal = get_norm(this, &normal);
	result = *m_normal;
	free_list((void *[]){normalLoc, m_normal}, 2);
	return (result);
}

t_vector	*get_locatione_at_intersection(t_object *this, t_ray *bckray,
		t_vector *params, t_vector *dir_v)
{
	double		dist;
	int			steps;
	t_vector	*cur_location;

	cur_location = copy_vector(*bckray->point1);
	steps = 0;
	while (TRUE)
	{
		dist = SDF(this, *cur_location, *params);
		cur_location = ms_addition(cur_location, num_muliplication(dir_v, dist),
			2);
		if (dist > 1e6 || steps >= MAX_STEPS)
		{
			delete_ray(bckray);
			free(cur_location);
			return (NULL);
		}
		if (dist < M_EPSILON)
			break ;
		steps++;
	}
	return (cur_location);
}

double	calculat_sdf_diff(t_object *this, t_vector *normal,
		t_vector displacemnt, t_vector parms)
{
	t_vector	*val1;
	t_vector	*val2;
	double		result;

	val1 = minus(normal, &displacemnt);
	val2 = addition(normal, &displacemnt);
	result = (SDF(this, *val2, parms) - SDF(this, *val1, parms));
	free_list((void *[]){val1, val2}, 2);
	return (result);
}

double	SDF(t_object *this, t_vector p, t_vector params)
{
	return (((t_rm_object_params *)this->extra)->torus_sdf(p, params));
}
