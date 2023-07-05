/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialBase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:51 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/05 12:04:51 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"

material_t	*new_material_base(double shininess_coefficient,
								double reflection_coefficient)
{
	material_t	*material_base;

	material_base = malloc(sizeof(material_t));
	material_base->reflection_coefficient = reflection_coefficient;
	material_base->shininess_coefficient = shininess_coefficient;
	material_base->transparency_coefficient = 0.0;
	material_base->reflactive_index = 1.0;
	return (material_base);
}

vector_t	*reflect_color(scene_t *scene, propretries_t *prop,
		t_color_params params)
{
	vector_t		*reflection_v;
	ray_t			*m_ray;
	propretries_t	local_prop;
	object_t		*c_obj;
	double			found_int;

	c_obj = NULL;
	reflection_v = Reflection_vector(params.camera_ray->m_lab,
										&prop->local_normal);
	m_ray = ray(&prop->int_point, addition(&prop->int_point, reflection_v));
	found_int = mt_cast_ray(scene, m_ray, &local_prop,
			(t_ref_cast_prop){params.cur_object, &c_obj});
	if (found_int && (params.rfc < MAX_REFLECTION_COUNT))
		return (c_obj->material->calculat_color(scene, &local_prop,
				(t_color_params){c_obj, m_ray, params.rfc + 1}));
	else
		return (vector(0, 0, 0));
}

int	mt_cast_ray(scene_t *scene, ray_t *m_ray, propretries_t *prop,
		t_ref_cast_prop cast_prop)
{
	t_list			*tmp;
	object_t		*obj;
	propretries_t	local_prop;
	double			min_dst;
	int				found_int;

	found_int = FALSE;
	min_dst = MAX_V;
	tmp = scene->m_object_list;
	while (tmp)
	{
		obj = (object_t *)tmp->content;
		if (obj != cast_prop.cur_object && obj->test_inter(obj, m_ray,
				&local_prop))
		{
			if (check_n_set_dist(&local_prop, m_ray, &min_dst))
			{
				found_int = TRUE;
				*cast_prop.c_obj = obj;
				*prop = local_prop;
			}
		}
		tmp = tmp->next;
	}
	return (found_int);
}

void	delete_material(material_t *this)
{
	if (this)
		free(this);
}
