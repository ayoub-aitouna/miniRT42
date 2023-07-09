/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayMarchingBase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:51 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 21:46:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/RayMarchingBase.h"

object_t *rm_object(vector_t *translation, vector_t *rotation,
					vector_t *scal, vector_t *color)
{
	object_t *rm_base_object;

	rm_base_object = object_base(translation, rotation, scal, color);
	rm_base_object->test_inter = rm_int_test;
	return (rm_base_object);
}

int rm_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	ray_t *bckray;
	vector_t *dir_v;
	vector_t *int_poi;
	vector_t *cur_location;

	bckray = Apply_transform(camera_ray, this, BCKWRD);
	dir_v = normilized_copy(bckray->m_lab);
	cur_location = get_locatione_at_intersection(this, bckray,
												 &(((t_rm_object_params *)this->extra)->params), dir_v);
	if (!cur_location)
	{
		free_list((void *[]){cur_location, dir_v}, 2);
		return (FALSE);
	}
	int_poi = Apply_transform_vector(cur_location, FRWRD, this);
	prop->local_normal = get_local_normal(this, cur_location, dir_v,
										  &(((t_rm_object_params *)this->extra)->params));
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	prop->poi = *cur_location;
	free_list((void *[]){cur_location, dir_v, int_poi},
			  3);
	delete_ray(bckray);
	return (TRUE);
}

vector_t get_local_normal(object_t *this, vector_t *cur_location,
						  vector_t *dir_v, vector_t *params)
{
	vector_t *normalLoc;
	vector_t normal;
	vector_t *m_normal;
	vector_t result;

	normalLoc = ms_minus(cur_location, num_muliplication(dir_v, 0.01), 1);
	normal = (vector_t){
		calculat_sdf_diff(this, normalLoc, (vector_t){D_S, 0.0, 0.0}, *params),
		calculat_sdf_diff(this, normalLoc, (vector_t){0.0, D_S, 0.0}, *params),
		calculat_sdf_diff(this, normalLoc, (vector_t){0.0, 0.0, D_S}, *params)};
	normalize(&normal);
	m_normal = get_norm(this, &normal);
	result = *m_normal;
	free_list((void *[]){normalLoc, m_normal}, 2);
	return (result);
}

vector_t *get_locatione_at_intersection(object_t *this, ray_t *bckray,
										vector_t *params, vector_t *dir_v)
{
	double dist;
	int steps;
	vector_t *cur_location;

	cur_location = copy_vector(*bckray->point1);
	steps = 0;
	while (TRUE)
	{
		dist = SDF(this, *cur_location, *params);
		cur_location = ms_addition(cur_location,
								   num_muliplication(dir_v, dist),
								   2);
		if (dist > 1e6 || steps >= MAX_STEPS)
		{
			delete_ray(bckray);
			free(cur_location);
			return (NULL);
		}
		if (dist < M_EPSILON)
			break;
		steps++;
	}
	return (cur_location);
}

double calculat_sdf_diff(object_t *this, vector_t *normal,
						 vector_t displacemnt, vector_t parms)
{
	vector_t *val1;
	vector_t *val2;
	double result;

	val1 = minus(normal, &displacemnt);
	val2 = addition(normal, &displacemnt);
	result = (SDF(this, *val2, parms) - SDF(this, *val1, parms));
	free_list((void *[]){val1, val2}, 2);
	return (result);
}

double SDF(object_t *this, vector_t p, vector_t params)
{
	return (((t_rm_object_params *)this->extra)->torus_sdf(p, params));
}
