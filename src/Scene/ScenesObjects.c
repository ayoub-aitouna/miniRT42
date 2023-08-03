/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenesObjects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:29:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:15:07 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

void	_set_up_material_configurations(t_object *this, float *coefficient,
			t_textures *texture);

t_object	*get_object_by_type(t_scene_object *s_obj)
{
	if (str_equal(s_obj->type, "sp"))
		return (create_sphere(s_obj->position, vector(0, 0, 0), s_obj->scal,
				convert_vec_color(s_obj->color)));
	if (str_equal(s_obj->type, "cy"))
		return (cylinder(s_obj->position, vector(-1.57, 0.0, 0.0), s_obj->scal,
				convert_vec_color(s_obj->color)));
	if (str_equal(s_obj->type, "co"))
		return (cone(s_obj->position, vector(0, 0, 0), s_obj->scal,
				convert_vec_color(s_obj->color)));
	if (str_equal(s_obj->type, "pl"))
		return (plane(s_obj->position, vector(0, 0, 0), vector(16.0, 16.0, 1.0),
				convert_vec_color(s_obj->color)));
	if (str_equal(s_obj->type, "torus"))
		return (torus(s_obj->position, vector(0, 0, 0), s_obj->scal,
				convert_vec_color(s_obj->color)));
	return (NULL);
}

t_textures	*get_texture(void *mlx_ptr, t_scene_object *s_obj)
{
	t_textures	*texture;
	char		**file_names;

	texture = NULL;
	if (s_obj->texture_type == NON)
		return (NULL);
	if (s_obj->texture_type == CHECKBOARD)
	{
		texture = new_texture((t_vector){0, 0, 0}, (t_vector){1.0, 1.0, 1.0});
		set_tfm(texture, &(t_vector2){0, 0}, &(t_vector2){4, 4}, 0);
	}
	else if (s_obj->texture_type == BUMPMAPTEXTURE)
	{
		file_names = ft_split(s_obj->texture_path, ',');
		if (!check_extention(file_names[0], ".xpm")
			&& !check_extention(file_names[1], ".xpm"))
			err("texture file has invalide extention \n");
		texture = new_img_texture(mlx_ptr, file_names[0], file_names[1]);
		free_list_str(file_names);
	}
	return (texture);
}

t_list	*objects(void *mlx, t_list *parsed)
{
	t_list			*data;
	t_object		*obj;
	t_scene_object	*s_obj;

	data = NULL;
	while (parsed)
	{
		s_obj = parsed->content;
		obj = get_object_by_type(s_obj);
		if (obj != NULL)
		{
			if (s_obj->normal)
				obj->normal = s_obj->normal;
			if (s_obj->reflection && s_obj->refraction)
				_set_up_material_configurations(obj, (float [])
				{s_obj->reflection->x,
					s_obj->reflection->y, s_obj->refraction->x,
					s_obj->refraction->y}, get_texture(mlx, s_obj));
			else
				_set_up_material_configurations(obj, NULL, NULL);
			push_back(&data, ft_lstnew(obj));
		}
		parsed = parsed->next;
	}
	return (data);
}

void	_set_up_material_configurations(t_object *this, float *coefficient,
		t_textures *texture)
{
	float	*local_coefficient;

	if (coefficient)
		local_coefficient = coefficient;
	else
		local_coefficient = (float []){0, 0, 0, 0};
	this->material->reflection_coefficient = local_coefficient[0];
	this->material->shininess_coefficient = local_coefficient[1];
	this->material->transparency_coefficient = local_coefficient[2];
	this->material->reflactive_index = local_coefficient[3];
	this->textures = texture;
}
