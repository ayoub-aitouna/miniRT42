/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/04 01:21:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

t_list	*light_source(t_list *parsed)
{
	t_list			*data;
	t_scene_object	*element;

	data = NULL;
	while (parsed)
	{
		element = ((t_scene_object *)parsed->content);
		if (str_equal(element->type, "L"))
			push_back(&data, ft_lstnew(new_light(element->position,
						convert_vec_color(element->color),
						element->intensity)));
		parsed = parsed->next;
	}
	return (data);
}

void	set_upcamera(t_scene *this, t_scene_object *val)
{
	this->m_camera = camera(val->field_of_view / 100, 1,
			(double)WIDTH / (double)HEIGHT);
	set_position(this->m_camera, val->position);
	set_up(this->m_camera, vector(0.001, 0.001, 1.0));
	set_loock_at(this->m_camera, val->normal);
	calculat_geometry(this->m_camera);
}

t_scene	*scene(void *mlx, void *mlx_win, t_list *parsed_list)
{
	t_scene			*scene;
	t_scene_object	*ambient_prop;

	(void)mlx_win;
	ambient_prop = first_of(parsed_list, "A");
	scene = malloc(sizeof(t_scene));
	scene->m_object_list = objects(mlx, parsed_list);
	scene->m_light_list = light_source(parsed_list);
	set_upcamera(scene, first_of(parsed_list, "C"));
	ambient_prop->color = ms_num_muliplication(ambient_prop->color,
			ambient_prop->intensity);
	convert_vec_color(ambient_prop->color);
	scene->ambient_light_factor = *ambient_prop->color;
	return (scene);
}

void	deletescene(t_scene *this)
{
	if (this)
	{
		delete_object_list(this->m_object_list);
		delete_light_list(this->m_light_list);
		deletecamera(this->m_camera);
		free(this);
	}
}
