/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:39 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:20 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/camera.h"

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

void	calculat_geometry(t_camera *this)
{
	t_vector	*aligment;

	aligment = minus(this->loockat, this->position);
	normalize(aligment);
		this->screen_u = cross(*aligment, *this->up);
	normalize(this->screen_u);
		this->screen_v = cross(*this->screen_u, *aligment);
	normalize(this->screen_v);
	this->screen_center = ms_addition(this->position,
			ms_num_muliplication(aligment, this->lenght), 1);
	this->screen_u = ms_num_muliplication(this->screen_u,
			this->horizontal_size);
	this->screen_v = ms_num_muliplication(this->screen_v, this->horizontal_size
			/ this->aspect_ration);
}

t_ray	*generate_ray(t_camera *this, double screenX, double screenY)
{
	t_vector	*w_part1;
	t_vector	*dst_cords;
	t_vector	*scalled_u;
	t_vector	*scalled_v;

	scalled_u = num_muliplication(this->screen_u, screenX);
	scalled_v = num_muliplication(this->screen_v, screenY);
	w_part1 = addition(this->screen_center, scalled_u);
	dst_cords = addition(w_part1, scalled_v);
	free(w_part1);
	free(scalled_v);
	free(scalled_u);
	return (ray(copy_vector(*this->position), dst_cords));
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
