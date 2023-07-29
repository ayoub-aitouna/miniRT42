/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/29 20:34:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

t_list	*light_source(void)
{
	t_list	*data;

	data = NULL;
	push_back(&data, ft_lstnew(new_light(vector(3.0, -10.0, -5.0), vector(1.0,
					1.0, 1.0), 4.0)));
	push_back(&data, ft_lstnew(new_light(vector(0.0, -10.0, -5.0), vector(1.0,
					1.0, 1.0), 2.0)));
	return (data);
}

void	set_upcamera(t_scene *this)
{
	this->m_camera = camera(1.8, 1, (double)WIDTH / (double)HEIGHT);
	set_position(this->m_camera, vector(-50.0, 0, 20.0));
	set_up(this->m_camera, vector(0.0, 0.0, 1.0));
	set_loock_at(this->m_camera, vector(0.0, 0.0, 1.0));
	calculat_geometry(this->m_camera);
}

t_scene	*scene(void *mlx, void *mlx_win)
{
	t_scene	*scene;

	(void)mlx_win;
	scene = malloc(sizeof(t_scene));
	scene->m_object_list = objects(mlx);
	scene->m_light_list = light_source();
	set_upcamera(scene);
	scene->ambient_light_factor = (t_vector){.x = (255.f / 255.f) * 0.2f,
		.y = (255.f / 255.f) * 0.2f, .z = (255.f / 255.f) * 0.2f};
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
