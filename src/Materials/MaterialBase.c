/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialBase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:51 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 22:06:59 by aaitouna         ###   ########.fr       */
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
	return (material_base);
}

vector_t	*reflect_color(scene_t *scene, propretries_t *prop,
		object_t *cur_object, ray_t *camera_ray, int rfc)
{
	vector_t		*reflection_v;
	ray_t			*m_ray;
	propretries_t	local_prop;
	object_t		*c_obj;
	double			found_int;
	vector_t		*color;

	c_obj = NULL;
	color = NULL;
	reflection_v = Reflection_vector(camera_ray->m_lab, &prop->local_normal);
	m_ray = ray(&prop->int_point, addition(&prop->int_point, reflection_v));
	found_int = mt_cast_ray(scene, m_ray, &local_prop, cur_object, &c_obj);
	if (found_int && (rfc < MAX_REFLECTION_COUNT))
		color = c_obj->material->calculat_color(scene, &local_prop, c_obj,
				m_ray, rfc + 1);
	else
		color = vector(0, 0, 0);
	return (color);
}


int	mt_cast_ray(scene_t *scene, ray_t *m_ray, propretries_t *prop,
		object_t *cur_object, object_t **c_obj)
{
	t_list			*tmp;
	object_t		*obj;
	propretries_t	local_prop;
	int				valide;
	double			min_dst;
	double			cur_dst;
	int				found_int;

	found_int = FALSE;
	min_dst = MAX_V;
	tmp = scene->m_object_list;
	while (tmp)
	{
		obj = (object_t *)tmp->content;
		if (obj != cur_object)
			valide = obj->test_inter(obj, m_ray, &local_prop);
		else
			valide = FALSE;
		if (valide)
		{
			cur_dst = vector_distance(m_ray->point1, &local_prop.int_point);
			if (cur_dst < min_dst)
			{
				found_int = TRUE;
				min_dst = cur_dst;
				*c_obj = obj;
				prop->int_point = local_prop.int_point;
				prop->local_normal = local_prop.local_normal;
				prop->local_color = local_prop.local_color;
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
