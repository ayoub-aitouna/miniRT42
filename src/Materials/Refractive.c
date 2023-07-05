/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refractive.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:22:08 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/05 11:35:35 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Refractive.h"

vector_t *refractive_color(scene_t *scene,
						   t_color_params params,
						   propretries_t *prop)
{
	ray_t *r_ray;
	ray_t *tmp_ray;
	propretries_t local_prop;
	object_t *c_obj;
	double r_i;
	int found_int;

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
		return (c_obj->material->calculat_color(scene, &local_prop,
												(t_color_params){c_obj, r_ray, params.rfc}));
	return (vector(0, 0, 0));
}

ray_t *reflacted_ray(ray_t *m_ray, double r, propretries_t *prop)
{
	vector_t *ray_norm;
	vector_t tmp_normal;
	vector_t *refractive_vector;
	double c;
	double f;

	ray_norm = normilized_copy(m_ray->m_lab);
	tmp_normal = prop->local_normal;
	c = -dot(tmp_normal, *ray_norm);
	if (c < 0.0)
	{
		tmp_normal = *num_muliplication(&tmp_normal, -1.0);
		c = -dot(tmp_normal, *ray_norm);
	}
	f = r * c - sqrtf(1.0 - pow(r, 2.0) * (1.0 - pow(c, 2.0)));
	vector_t *rp = num_muliplication(ray_norm, r);
	refractive_vector =
		addition(rp, num_muliplication(&tmp_normal, f));
	return ray(addition(&prop->int_point, num_muliplication(refractive_vector, 0.01)),
			   addition(&prop->int_point, refractive_vector));
}
