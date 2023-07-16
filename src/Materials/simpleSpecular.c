/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleSpecular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:52:29 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:30 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"
#include "headers/SimpleMaterial.h"
#include <stdlib.h>

t_vector	*calculat_specular_color(t_scene *scene, t_propretries *prop,
		t_object *cur_object, t_ray *camera_ray)
{
	t_list		*tmp;
	t_vector	*specular_color;
	t_ray		*lighit_ray;
	double		specular_intensity;

	tmp = scene->m_light_list;
	specular_color = vector(0.f, 0.f, 0.f);
	while (tmp)
	{
		lighit_ray = generate_light_ray(((t_light *)tmp->content),
			&prop->int_point);
		if (spec_int_test(scene, lighit_ray))
		{
			delete_ray(lighit_ray);
			return (specular_color);
		}
		specular_intensity = calculat_spec_intensity(lighit_ray, camera_ray,
			&prop->local_normal, cur_object);
		specular_color->x += ((t_light *)tmp->content)->base_color->x
			* specular_intensity;
		specular_color->y += ((t_light *)tmp->content)->base_color->y
			* specular_intensity;
		specular_color->z += ((t_light *)tmp->content)->base_color->z
			* specular_intensity;
		tmp = tmp->next;
		delete_ray(lighit_ray);
	}
	return (specular_color);
}

int	spec_int_test(t_scene *scene, t_ray *lighit_ray)
{
	int				valide_itersection;
	t_list			*t_objectmp;
	t_object		*obj;
	t_propretries	local_prop;

	valide_itersection = FALSE;
	t_objectmp = scene->m_object_list;
	while (t_objectmp)
	{
		obj = ((t_object *)t_objectmp->content);
		valide_itersection = obj->test_inter(obj, lighit_ray, &local_prop);
		if (valide_itersection)
			break ;
		t_objectmp = t_objectmp->next;
	}
	return (valide_itersection);
}

t_ray	*generate_light_ray(t_light *light, t_vector *initPoint)
{
	t_vector	*light_dir;
	t_vector	*start_pos;
	t_ray		*light_ray;

	light_dir = normalized_sub(light->position, initPoint);
	start_pos = ms_addition(initPoint, num_muliplication(light_dir, 0.001), 1);
	light_ray = (ray(copy_vector(*start_pos), addition(start_pos, light_dir)));
	free_list((void *[]){light_dir, start_pos}, 2);
	return (light_ray);
}

double	calculat_spec_intensity(t_ray *light_ray, t_ray *camera_ray,
		t_vector *localNormal, t_object *cur_object)
{
	t_vector	*m_reflection_vector;
	t_vector	*v;
	double		dot_product;
	double		specular_intensity;

	specular_intensity = 0;
	m_reflection_vector = reflection_vector(light_ray->m_lab, localNormal);
	v = normalized(camera_ray->m_lab);
	dot_product = dot(*m_reflection_vector, *v);
	free_list((void *[]){m_reflection_vector, v}, 2);
	if (dot_product > 0.0)
		specular_intensity = cur_object->material->reflection_coefficient
			* pow(dot_product, cur_object->material->shininess_coefficient);
	return (specular_intensity);
}
