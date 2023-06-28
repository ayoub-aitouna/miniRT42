/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:37 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:22:38 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pointlight.h"

light_t	*new_light(vector_t *position, vector_t *color, double intensity)
{
	light_t	*light;

	light = malloc(sizeof(light_t));
	light->base_color = color;
	light->m_intensity = intensity;
	light->position = position;
	return (light);
}

int	check_ray_path(light_t *this, scene_t *scene, vector_t *initPoint,
		object_t *cur_Object, vector_t *lightDir)
{
	t_list			*tmp;
	ray_t			*m_ray;
	int				valide_i;
	double			*distances;
	propretries_t	prop;

	distances = (double[]){0.f, 0.f};
	m_ray = ray(copy_vector(*initPoint), copy_vector(*this->position));
	distances[0] = vector_distance(this->position, initPoint);
	valide_i = FALSE;
	tmp = scene->m_object_list;
	while (tmp)
	{
		if (((object_t *)tmp->content) != NULL)
		{
			if (((object_t *)tmp->content) != cur_Object)
			{
				valide_i = ((object_t *)tmp->content)->test_inter(((object_t *)tmp->content),
						m_ray, &prop);
				distances[1] = vector_distance(&prop.int_point, m_ray->point1);
				if (distances[1] > distances[0])
					valide_i = FALSE;
				if (valide_i)
				{
					free(lightDir);
					delete_ray(m_ray);
					return (FALSE);
				}
			}
		}
		tmp = tmp->next;
	}
	delete_ray(m_ray);
	return (TRUE);
}

/**
 * @brief I = Li * (1 - (angle / (PI/2) ))

	* @brief angle(angle btween localnormal & lightDir) = cos^-1(localNormal.lightDir)
 * @return light Intesity as double
 */
int	calculatIlumination(light_t *this, vector_t *localNormal,
		vector_t *initPoint, double *intensity, vector_t *Color, scene_t *scene,
		object_t *cur_Object)
{
	vector_t	*lightDir;
	double		angle;

	lightDir = minus(this->position, initPoint);
	normalize(lightDir);
	if (!check_ray_path(this, scene, initPoint, cur_Object, lightDir))
		return (FALSE);
	angle = acos(dot(*localNormal, *lightDir));
	free(lightDir);
	if (angle > HALFPI)
		return (FALSE);
	*Color = *this->base_color;
	*intensity = (this->m_intensity * (1 - (angle / HALFPI)));
	return (TRUE);
}

void	delete_light(light_t *this)
{
	if (this)
	{
		if (this->base_color)
			free(this->base_color);
		if (this->position)
			free(this->position);
		free(this);
	}
}

void	delete_light_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		delete_light(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}