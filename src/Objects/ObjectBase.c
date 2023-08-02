/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectBase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:24 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/02 11:05:31 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Objectbase.h"

t_object	*object_base(t_vector *translation, t_vector *rotation,
		t_vector *scal, t_vector *color)
{
	t_object	*object;

	object = (t_object *)malloc(sizeof(t_object));
	object->fwd_tfm = set_transform(translation, rotation, scal);
	object->bck_tfm = inverse(object->fwd_tfm);
	object->base_color = copy_vector(*color);
	object->material = new_simple_material(0, 0);
	object->textures = NULL;
	set_lineartfm(object);
	free_list((void *[]){translation, rotation, scal, color}, 4);
	return (object);
}

/// @brief Delete Operator Overload
/// @param t_object *
void	delete_object_base(t_object *this)
{
	if (this)
	{
		if (this->base_color)
			free(this->base_color);
		if (this->bck_tfm)
			delete_matrix(this->bck_tfm);
		if (this->lineartfm)
			delete_matrix(this->lineartfm);
		if (this->fwd_tfm)
			delete_matrix(this->fwd_tfm);
		if (this->material)
			delete_material(this->material);
		if (this->textures)
			delete_textures(this->textures);
		free(this);
	}
}

int	close_enough(double v1, double v2)
{
	return (fabs(v1 - v2) < EPSILON);
}

t_vector	*false(int *status)
{
	*status = FALSE;
	return (NULL);
}

/// @brief Delete[] Operator Overload
/// @param t_object *
void	delete_object_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		delete_object_base(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}
