/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GeneratRay.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 20:19:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/04 01:02:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/camera.h"

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
