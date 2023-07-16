/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:37 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:07 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/pointlight.h"

t_light	*new_light(t_vector *position, t_vector *color, double intensity)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	light->base_color = color;
	light->m_intensity = intensity;
	light->position = position;
	return (light);
}

void	delete_light(t_light *this)
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
