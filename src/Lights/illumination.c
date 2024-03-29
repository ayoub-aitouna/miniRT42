/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 14:18:02 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:07 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pointlight.h"

int	check_ray_path_returns(int value, t_ray *m_ray)
{
	delete_ray(m_ray);
	return (value);
}

int	check_ray_path(t_light *this, t_light_params params, t_vector *initPoint)
{
	t_list			*tmp;
	t_ray			*m_ray;
	int				valide_i;
	double			distances[2];
	t_propretries	prop;

	m_ray = ray(copy_vector(*initPoint), copy_vector(*this->position));
	distances[0] = vector_distance(this->position, initPoint);
	tmp = params.scene->m_object_list;
	while (tmp)
	{
		if (((t_object *)tmp->content) != params.cur_object)
		{
			valide_i = ((t_object *)tmp->content)->test_inter(((t_object *)tmp
						->content), m_ray, &prop);
			distances[1] = vector_distance(&prop.int_point, m_ray->point1);
			if (distances[1] > distances[0])
				valide_i = FALSE;
			if (valide_i)
				return (check_ray_path_returns(FALSE, m_ray));
		}
		tmp = tmp->next;
	}
	return (check_ray_path_returns(TRUE, m_ray));
}

/**
 * @brief I = Li * (1 - (angle / (PI/2) ))
 * @brief angle(angle btween localnormal & lightDir)
 *	= cos^-1(localNormal.lightDir)
 * @return light Intesity as double
 */
int	calculat_ilumination(t_light *this, t_propretries *prop,
		t_light_params params)
{
	t_vector	*light_dir;
	double		angle;

	if (!check_ray_path(this, params, &prop->int_point))
		return (FALSE);
	light_dir = normalized_sub(this->position, &prop->int_point);
	angle = acos(dot(*&prop->local_normal, *light_dir));
	free(light_dir);
	if (angle > HALFPI)
		return (FALSE);
	*params.color = *this->base_color;
	*params.intensity = (this->m_intensity * (1 - (angle / HALFPI)));
	return (TRUE);
}
