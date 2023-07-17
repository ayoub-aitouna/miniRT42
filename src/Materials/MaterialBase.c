/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialBase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:51 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/17 19:14:21 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"

t_material	*new_material_base(double shininess_coefficient,
		double reflection_coefficient)
{
	t_material	*material_base;

	material_base = malloc(sizeof(t_material));
	material_base->reflection_coefficient = reflection_coefficient;
	material_base->shininess_coefficient = shininess_coefficient;
	material_base->transparency_coefficient = 0.0;
	material_base->reflactive_index = 1.0;
	return (material_base);
}

t_vector	*reflect_color(t_scene *scene, t_propretries *prop,
		t_color_params params)
{
	t_vector		*reflection_v;
	t_ray			*m_ray;
	t_propretries	local_prop;
	t_object		*c_obj;
	t_vector		*color;

	c_obj = NULL;
	reflection_v = reflection_vector(params.camera_ray->m_lab,
			&prop->local_normal);
	m_ray = ray(copy_vector(prop->int_point), ms_addition(&prop->int_point,
				reflection_v, 1));
	if (mt_cast_ray(scene, m_ray, &local_prop,
			(t_ref_cast_prop){params.cur_object, &c_obj})
		&& (params.rfc < MAX_REFLECTION_COUNT))
	{
		color = (c_obj->material->calculat_color(scene, &local_prop,
					(t_color_params){c_obj, m_ray, params.rfc + 1}));
		delete_ray(m_ray);
		return (color);
	}
	else
	{
		delete_ray(m_ray);
		return (vector(0, 0, 0));
	}
}

int	mt_cast_ray(t_scene *scene, t_ray *m_ray, t_propretries *prop,
		t_ref_cast_prop cast_prop)
{
	t_list			*tmp;
	t_object		*obj;
	t_propretries	local_prop;
	double			min_dst;
	int				found_int;

	found_int = FALSE;
	min_dst = MAX_V;
	tmp = scene->m_object_list;
	while (tmp)
	{
		obj = (t_object *)tmp->content;
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

t_vector	get_curect_color(t_object *this, t_propretries *prop)
{
	t_vector	*color;
	t_vector	result;

	if (this->textures)
	{
		color = this->textures->get_color(this->textures, prop->uv_cords);
		result = *color;
		free(color);
		return (result);
	}
	return (prop->local_color);
}

void	delete_material(t_material *this)
{
	if (this)
		free(this);
}
