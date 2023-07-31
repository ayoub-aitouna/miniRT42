/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ScenesObjects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:29:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/31 18:01:02 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

t_list *objects(void *mlx, t_list *parsed)
{
	t_list *data;
	t_object *sphere;
	t_object *sphere2;
	t_object *sphere3;
	t_object *m_torus;
	t_object *floor;
	t_object *image;
	t_textures *checker;
	t_textures *ww;
	t_textures *brick;

	data = NULL;
	(void)mlx;
	(void)parsed;
	(void)brick;
	(void)ww;
	checker = new_texture((t_vector){1.0, 1.0, 1.0}, (t_vector){0.2, 0.2, 0.2});
	set_tfm(checker, &(t_vector2){.x = 0, .y = 0}, &(t_vector2){.x = 16, .y = 16}, 0);
	ww = new_img_texture(mlx, "./assets/ww.xpm", NULL);
	brick = new_img_texture(mlx, "./assets/brick.xpm", NULL);
	floor = plane(vector(.0, 0.0, 1.0), vector(0.0, 0, 0), vector(16.0, 16.0, 1.0), vector(1, 1, 1.0));
	floor->normal = vector(0,0,1);
	image = plane(vector(0.0, 5.0, -0.75), vector(-PI / 2.0, 0.0, 0.0),
				  vector(1.75, 1.75, 1.0), vector(1, 1, 1.0));
	image->normal = vector(0, 0, 1);
	sphere = create_sphere(vector(-2.0, -2.0, 0.25), vector(HALFPI, HALFPI, HALFPI), vector(0.75, 0.75, 0.75), vector(1.0, 0.2, 0.2));
	sphere2 = create_sphere(vector(-2.0, -0.5, 0.25), vector(0.0, 0.0, 0.0),
							vector(0.75, 0.75, 0.75), vector(0.2, 1.0, 0.2));
	sphere3 = create_sphere(vector(-2.0, -1.25, -1.0), vector(0.0, 0.0, 0.0),
							vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));
	m_torus = torus(vector(2.0, -1.25, 0.25), vector(HALFPI, 0.0, 0.0),
					vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));
	set_up_material_configurations(floor, &(t_vector){0.25, 32.0, 0.0}, 0.0, checker);
	set_up_material_configurations(image, &(t_vector){0.00, 0.00, 0.0}, 0.0, ww);
	// set_up_material_configurations(sphere, &(t_vector){0.25, 32.0, 0.0}, 0.0, checker);
	// set_up_material_configurations(sphere2, &(t_vector){0.55, 32.0, 0.3}, 1.33, NULL);
	// set_up_material_configurations(sphere3, &(t_vector){0.35, 32.0, 0.0}, 0.0, NULL);
	// set_up_material_configurations(m_torus, &(t_vector){0.25, 32.0, 0.35}, 1.333, brick);
	push_back(&data, ft_lstnew(floor));
	push_back(&data, ft_lstnew(sphere));
	push_back(&data, ft_lstnew(sphere2));
	push_back(&data, ft_lstnew(sphere3));
	push_back(&data, ft_lstnew(m_torus));
	push_back(&data, ft_lstnew(image));
	return (data);
}

t_object *get_object_by_type(t_scene_object *s_obj)
{
	if (str_equal(s_obj->type, "sp"))
		return (create_sphere(s_obj->position, vector(0, 0, 0), s_obj->scal,
							  convert_vec_color(s_obj->color)));
	if (str_equal(s_obj->type, "cy"))
		return (cylinder(s_obj->position, vector(0, 0, 0), s_obj->scal,
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

t_textures *get_texture(void *mlx_ptr, t_scene_object *s_obj)
{
	t_textures *texture;
	char **file_names;

	texture = NULL;
	if (s_obj->texture_type == NON)
		return NULL;
	if (s_obj->texture_type == CHECKBOARD)
	{
		texture = new_texture((t_vector){0, 0, 0}, (t_vector){1.0, 1.0, 1.0});
		set_tfm(texture, &(t_vector2){0, 0}, &(t_vector2){4, 4}, 0);
	}
	else if (s_obj->texture_type == BUMPMAPTEXTURE)
	{
		file_names = ft_split(s_obj->Texture_path, ',');
		texture = new_img_texture(mlx_ptr, file_names[0], file_names[1]);
		free_list_str(file_names);
	}
	return (texture);
}

t_list *___diabled___objects(void *mlx, t_list *parsed)
{
	t_list *data;
	t_object *obj;
	t_scene_object *s_obj;

	data = NULL;
	while (parsed)
	{
		s_obj = parsed->content;
		obj = get_object_by_type(s_obj);
		if (obj != NULL)
		{
			if (s_obj->normal)
				obj->normal = s_obj->normal;
			set_up_material_configurations(
				obj, &(t_vector){0.00, 0.00, 0.0}, 0.0, get_texture(mlx, s_obj));
			push_back(&data, ft_lstnew(obj));
		}
		obj = NULL;
		parsed = parsed->next;
	}
	return (data);
}

void set_up_material_configurations(t_object *this, t_vector *material_prop,
									double bending_index, t_textures *texture)
{
	this->material->reflection_coefficient = material_prop->x;
	this->material->shininess_coefficient = material_prop->y;
	this->material->transparency_coefficient = material_prop->z;
	this->material->reflactive_index = bending_index;
	this->textures = texture;
}
