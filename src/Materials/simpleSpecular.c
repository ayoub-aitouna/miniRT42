/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simpleSpecular.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 09:52:29 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/02 10:16:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"
#include "headers/SimpleMaterial.h"
#include <stdlib.h>

vector_t	*calculat_specular_color(scene_t *scene, propretries_t *prop,
		object_t *cur_object, ray_t *camera_ray)
{
	t_list		*tmp;
	vector_t	*specular_color;
	ray_t		*lighit_ray;
	double		specular_intensity;

	tmp = scene->m_light_list;
	specular_color = vector(0.f, 0.f, 0.f);
	while (tmp)
	{
		lighit_ray = generate_light_ray(((light_t *)tmp->content),
				&prop->int_point);
		if (spec_int_test(scene, lighit_ray))
			return (specular_color);
		specular_intensity = calculat_spec_intensity(lighit_ray, camera_ray,
				&prop->local_normal, cur_object);
		specular_color->x += ((light_t *)tmp->content)->base_color->x
			* specular_intensity;
		specular_color->y += ((light_t *)tmp->content)->base_color->y
			* specular_intensity;
		specular_color->z += ((light_t *)tmp->content)->base_color->z
			* specular_intensity;
		tmp = tmp->next;
		delete_ray(lighit_ray);
	}
	return (specular_color);
}

int	spec_int_test(scene_t *scene, ray_t *lighit_ray)
{
	int				valide_itersection;
	t_list			*object_tmp;
	object_t		*obj;
	propretries_t	local_prop;

	valide_itersection = FALSE;
	object_tmp = scene->m_object_list;
	while (object_tmp)
	{
		obj = ((object_t *)object_tmp->content);
		valide_itersection = obj->test_inter(obj, lighit_ray, &local_prop);
		if (valide_itersection)
			break ;
		object_tmp = object_tmp->next;
	}
	return (valide_itersection);
}

ray_t	*generate_light_ray(light_t *light, vector_t *initPoint)
{
	vector_t	*light_dir;
	vector_t	*start_pos;
	ray_t		*light_ray;

	light_dir = normalized_sub(light->position, initPoint);
	start_pos = ms_addition(initPoint, num_muliplication(light_dir, 0.001), 1);
	light_ray = (ray(copy_vector(*start_pos), addition(start_pos, light_dir)));
	free_list((void *[]){light_dir, start_pos}, 2);
	return (light_ray);
}

double	calculat_spec_intensity(ray_t *light_ray,
								ray_t *camera_ray,
								vector_t *localNormal,
								object_t *cur_object)
{
	vector_t	*reflection_vector;
	vector_t	*v;
	double		dot_product;
	double		specular_intensity;

	specular_intensity = 0;
	reflection_vector = Reflection_vector(light_ray->m_lab, localNormal);
	v = normalized(camera_ray->m_lab);
	dot_product = dot(*reflection_vector, *v);
	free_list((void *[]){reflection_vector, v}, 2);
	if (dot_product > 0.0)
		specular_intensity = cur_object->material->reflection_coefficient
			* pow(dot_product, cur_object->material->shininess_coefficient);
	return (specular_intensity);
}
