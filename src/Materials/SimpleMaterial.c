/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleMaterial.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/05 12:45:44 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/MaterialBase.h"
#include "headers/SimpleMaterial.h"
#include <stdlib.h>

material_t *new_simple_material(double shininess_coefficient,
								double reflection_coefficient)
{
	material_t *simple_material;

	simple_material = new_material_base(shininess_coefficient,
										reflection_coefficient);
	simple_material->calculat_color = calculat_color;
	return (simple_material);
}

vector_t *calculat_color(scene_t *scene, propretries_t *prop,
						 t_color_params c_params)
{
	vector_t *color;
	vector_t *over_all_color;
	vector_t *specular_color;
	vector_t *reflection_color;
	double reflectivity;

	specular_color = NULL;
	reflection_color = NULL;
	reflectivity = c_params.cur_object->material->reflection_coefficient;
	prop->local_color = get_curect_color(c_params.cur_object, prop);
	color = calculat_diffuse_color(scene, prop, c_params.cur_object);
	if (c_params.cur_object->material->reflection_coefficient > 0.f)
		reflection_color = reflect_color(scene, prop, c_params);
	if (reflection_color)
		over_all_color = ms_addition(num_muliplication(reflection_color,
													   reflectivity),
									 num_muliplication(color, (1 - reflectivity)),
									 2);
	else
		over_all_color = color;
	over_all_color = get_refractive_color(over_all_color, scene, c_params,
										  prop);
	if (c_params.cur_object->material->shininess_coefficient > 0.f)
		specular_color = calculat_specular_color(scene, prop,
												 c_params.cur_object, c_params.camera_ray);
	if (specular_color)
		over_all_color = ms_addition(over_all_color, specular_color, 2);
	return (over_all_color);
}

vector_t *get_refractive_color(vector_t *color, scene_t *scene,
							   t_color_params params, propretries_t *prop)
{
	vector_t *r_color;
	vector_t *final_color;
	double transparency;

	transparency = params.cur_object->material->transparency_coefficient;
	if (!transparency)
		return (color);
	r_color = refractive_color(scene, params, prop);
	final_color = ms_addition(num_muliplication(r_color,
												transparency),
							  num_muliplication(color, (1 - transparency)),
							  2);
	free(color);
	return (final_color);
}

vector_t *
calculat_diffuse_color(scene_t *scene, propretries_t *prop,
					   object_t *cur_object)
{
	vector_t color;
	vector_t *final_color;
	t_list *tmp;
	double intensity;
	int valid_ilum;

	valid_ilum = 0;
	final_color = copy_vector(scene->ambient_light_factor);
	tmp = scene->m_light_list;
	while (tmp)
	{
		valid_ilum = calculat_ilumination(tmp->content, prop,
										  (t_light_params){.intensity = &intensity, .color = &color, .scene = scene, .cur_object = cur_object});
		if (valid_ilum)
		{
			final_color->x += (color.x * intensity);
			final_color->y += (color.y * intensity);
			final_color->z += (color.z * intensity);
		}
		tmp = tmp->next;
	}
	return (ms_muliplication(final_color, &prop->local_color, 0));
}

vector_t get_curect_color(object_t *this, propretries_t *prop)
{
	if (this->textures)
		return (*this->textures->get_color(this->textures, prop->uv_cords));
	return (prop->local_color);
}
