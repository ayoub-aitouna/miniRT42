/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/31 17:08:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

t_list *light_source(t_list *parsed)
{
	t_list *data;
	t_scene_object *element;

	data = NULL;
	while (parsed)
	{
		element = ((t_scene_object *)parsed->content);
		if (str_equal(element->type, "L"))
			push_back(&data, ft_lstnew(new_light(element->position,
												 convert_vec_color(element->color), element->intensity)));
		parsed = parsed->next;
	}
	return (data);
}
t_vector *get_up_vector(t_vector *position, t_vector *loock_at)
{
	t_vector	*norm;
	t_vector	*right;
	t_vector	*initial_up;
	t_vector	*up;
	
	norm = normalized_sub(loock_at, position);
	initial_up = vector(0,0,-1);
	right = cross(*norm, *initial_up);
	up = cross(*right, *norm);
	print_vector(*position);
	print_vector(*loock_at);
	print_vector(*norm);
	print_vector(*right);
	print_vector(*up);
	printf("\n\n");
	free_list((void *[]){norm, initial_up, right}, 3);
	return (up);
}

void set_upcamera(t_scene *this, t_scene_object *camera_prop)
{
	this->m_camera = camera(camera_prop->field_of_view / 100, 1, (double)WIDTH / (double)HEIGHT);
	set_position(this->m_camera, camera_prop->position);
	set_up(this->m_camera, vector(0.0, 0.0, 1.0));
	set_loock_at(this->m_camera, camera_prop->normal);
	calculat_geometry(this->m_camera);
}

t_scene *scene(void *mlx, void *mlx_win, t_list *parsed_list)
{
	t_scene *scene;
	t_scene_object *ambient_prop;

	(void)mlx_win;
	ambient_prop = first_of(parsed_list, "A");
	scene = malloc(sizeof(t_scene));
	scene->m_object_list = objects(mlx, parsed_list);
	scene->m_light_list = light_source(parsed_list);
	set_upcamera(scene, first_of(parsed_list, "C"));
	scene->ambient_light_factor = (t_vector){.x = (ambient_prop->color->x / 255.f) * 0.2f, .y = (ambient_prop->color->y / 255.f) * 0.2f, .z = (ambient_prop->color->z / 255.f) * ambient_prop->intensity};
	return (scene);
}

void deletescene(t_scene *this)
{
	if (this)
	{
		delete_object_list(this->m_object_list);
		delete_light_list(this->m_light_list);
		deletecamera(this->m_camera);
		free(this);
	}
}
