/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:37 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 14:20:42 by aaitouna         ###   ########.fr       */
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
	t_list	*tmp;

	while (list)
	{
		delete_light(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
