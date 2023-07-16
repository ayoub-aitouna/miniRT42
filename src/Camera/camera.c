/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:39 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 20:19:57 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/camera.h"

t_camera	*camera(double horizontal_size, double lenght, double aspect_ration)
{
	t_camera	*camera;

	camera = malloc(sizeof(t_camera));
	camera->position = NULL;
	camera->loockat = NULL;
	camera->up = NULL;
	camera->horizontal_size = horizontal_size;
	camera->lenght = lenght;
	camera->aspect_ration = aspect_ration;
	return (camera);
}

void	set_position(t_camera *this, t_vector *position)
{
	this->position = position;
}

void	set_up(t_camera *this, t_vector *Up)
{
	this->up = Up;
}

void	set_loock_at(t_camera *this, t_vector *loockat)
{
	this->loockat = loockat;
}

void	deletecamera(t_camera *this)
{
	if (this)
	{
		if (this->position)
			free(this->position);
		if (this->loockat)
			free(this->loockat);
		if (this->up)
			free(this->up);
		if (this->screen_u)
			free(this->screen_u);
		if (this->screen_v)
			free(this->screen_v);
		if (this->screen_center)
			free(this->screen_center);
		free(this);
	}
}
