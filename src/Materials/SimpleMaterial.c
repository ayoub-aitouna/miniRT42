/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleMaterial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 20:19:11 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"
#include "headers/SimpleMaterial.h"
#include <stdlib.h>

material_t	*new_simple_material(double shininess_coefficient,
								double reflection_coefficient)
{
	material_t	*simple_material;

	simple_material = new_material_base(shininess_coefficient,
										reflection_coefficient);
	simple_material->calculat_color = calculat_color;
	return (simple_material);
}
vector_t	get_curect_color(object_t *this, propretries_t *prop)
{
	if (this->textures)
		return (*this->textures->get_color(this->textures, prop->uv_cords));
	return (prop->local_color);
}
vector_t	*calculat_color(scene_t *scene, propretries_t *prop,
		object_t *cur_object, ray_t *camera_ray, int rfc)
{
	vector_t	*color;
	vector_t	*over_all_color;
	vector_t	*specularColor;
	vector_t	*reflectionColor;
	double		reflectivity;

	specularColor = NULL;
	reflectionColor = NULL;
	reflectivity = cur_object->material->reflection_coefficient;
	prop->local_color = get_curect_color(cur_object, prop);
	color = CalculatDiffuseColor(scene, prop, cur_object);
	if (cur_object->material->reflection_coefficient > 0.f)
		reflectionColor = reflect_color(scene, prop, cur_object, camera_ray,
				rfc);
	if (reflectionColor)
		over_all_color =
			ms_addition(num_muliplication(reflectionColor, reflectivity),
						num_muliplication(color, (1 - reflectivity)),
						2);
	else
		over_all_color = color;
	if (cur_object->material->shininess_coefficient > 0.f)
		specularColor = Calculat_specularColor(scene, &prop->local_normal,
				&prop->int_point, cur_object, camera_ray);
	if (specularColor)
		over_all_color = ms_addition(over_all_color, specularColor, 2);
	return (over_all_color);
}

vector_t	*Calculat_specularColor(scene_t *scene, vector_t *localNormal,
		vector_t *initPoint, object_t *cur_object, ray_t *camera_ray)
{
	t_list			*tmp;
	object_t		*obj;
	light_t			*light;
	propretries_t	local_prop;
	vector_t		*light_dir;
	vector_t		*specularColor;
	vector_t		*start_pos;
	ray_t			*lighit_ray;
	vector_t		*reflection_vector;
	int				valide_itersection;
	double			specular_intensity;
	t_list			*object_tmp;
	vector_t		*v;
	double			dotProduct;

	tmp = scene->m_light_list;
	specularColor = vector(0.f, 0.f, 0.f);
	while (tmp)
	{
		light = (light_t *)tmp->content;
		specular_intensity = 0;
		light_dir = normalized_sub(light->position, initPoint);
		start_pos = ms_addition(initPoint, num_muliplication(light_dir, 0.001),
				1);
		lighit_ray = ray(copy_vector(*start_pos), addition(start_pos,
					light_dir));
		valide_itersection = FALSE;
		object_tmp = scene->m_object_list;
		while (object_tmp)
		{
			obj = (object_t *)object_tmp->content;
			valide_itersection = obj->test_inter(obj, lighit_ray, &local_prop);
			if (valide_itersection)
				break ;
			object_tmp = object_tmp->next;
		}
		if (!valide_itersection)
		{
			reflection_vector = Reflection_vector(lighit_ray->m_lab,
													localNormal);
			v = normalized(camera_ray->m_lab);
			dotProduct = dot(*reflection_vector, *v);
			free_list((void *[]){reflection_vector, v}, 2);
			if (dotProduct > 0.0)
				specular_intensity = cur_object->material->reflection_coefficient
					* pow(dotProduct,
						cur_object->material->shininess_coefficient);
			specularColor->x += light->base_color->x * specular_intensity;
			specularColor->y += light->base_color->y * specular_intensity;
			specularColor->z += light->base_color->z * specular_intensity;
		}
		tmp = tmp->next;
		free_list((void *[]){light_dir, start_pos}, 2);
		delete_ray(lighit_ray);
	}
	return (specularColor);
}

vector_t	*CalculatDiffuseColor(scene_t *scene, propretries_t *prop,
		object_t *cur_object)
{
	vector_t	Color;
	vector_t	*final_color;
	t_list		*tmp;
	double		intensity;
	int			validIlum;

	validIlum = 0;
	final_color = copy_vector(scene->ambient_light_factor);
	tmp = scene->m_light_list;
	while (tmp)
	{
		validIlum = calculat_ilumination(tmp->content, prop,
				(t_light_params){.intensity = &intensity, .color = &Color,
				.scene = scene, .cur_object = cur_object});
		if (validIlum)
		{
			final_color->x += (Color.x * intensity);
			final_color->y += (Color.y * intensity);
			final_color->z += (Color.z * intensity);
		}
		tmp = tmp->next;
	}
	return (ms_muliplication(final_color, &prop->local_color, 0));
}
