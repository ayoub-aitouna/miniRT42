/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refractive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:22:08 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:30 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Refractive.h"

t_vector	*refractive_color(t_scene *scene, t_color_params params,
		t_propretries *prop)
{
	t_ray			*r_ray;
	t_ray			*tmp_ray;
	t_propretries	local_prop;
	t_object		*c_obj;
	t_vector		*color;
	double			r_i;
	int				found_int;

	local_prop = *prop;
	r_i = params.cur_object->material->reflactive_index;
	c_obj = NULL;
	r_ray = reflacted_ray(params.camera_ray, (1.f / r_i), &local_prop);
	if (params.cur_object->test_inter(params.cur_object, r_ray, &local_prop))
	{
		tmp_ray = reflacted_ray(r_ray, r_i, &local_prop);
		delete_ray(r_ray);
		r_ray = tmp_ray;
	}
	found_int = mt_cast_ray(scene, r_ray, &local_prop,
		(t_ref_cast_prop){params.cur_object, &c_obj});
	if (found_int)
		color = (c_obj->material->calculat_color(scene, &local_prop,
				(t_color_params){c_obj, r_ray, params.rfc}));
	else
		color = (vector(0, 0, 0));
	delete_ray(r_ray);
	return (color);
}

t_ray	*reflacted_ray(t_ray *m_ray, double r, t_propretries *prop)
{
	t_vector	*ray_norm;
	t_vector	*tmp_normal;
	t_vector	*refractive_vector;
	double		c;
	double		f;
	t_vector	*p1;
	t_vector	*p2;

	ray_norm = normilized_copy(m_ray->m_lab);
	tmp_normal = copy_vector(prop->local_normal);
	c = -dot(*tmp_normal, *ray_norm);
	if (c < 0.0)
	{
		tmp_normal = ms_num_muliplication(tmp_normal, -1.0);
		c = -dot(*tmp_normal, *ray_norm);
	}
	f = r * c - sqrtf(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)));
	refractive_vector = ms_addition(num_muliplication(ray_norm, r),
		num_muliplication(tmp_normal, f), 2);
	free_list((void *[]){ray_norm, tmp_normal}, 2);
	p1 = ms_addition(copy_vector(prop->int_point),
		num_muliplication(refractive_vector, 0.01), 2);
	p2 = ms_addition(copy_vector(prop->int_point), refractive_vector, 2);
	return (ray(p1, p2));
}
