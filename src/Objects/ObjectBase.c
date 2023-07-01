/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ObjectBase.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:24 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 08:50:43 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/base.h"

object_t	*object_base(vector_t *translation, vector_t *rotation,
		vector_t *scal, vector_t *color)
{
	object_t	*object;

	object = (object_t *)malloc(sizeof(object_t));
	object->fwd_tfm = Set_transform(translation, rotation, scal);
	object->bck_tfm = inverse(object->fwd_tfm);
	object->base_color = copy_vector(*color);
	object->material = new_simple_material(0, 0);
	object->textures = NULL;
	set_lineartfm(object);
	free_list((void *[]){translation, rotation, scal, color}, 4);
	return (object);
}

/// @brief Delete Operator Overload
/// @param object_t *
void	deleteObjectBase(object_t *this)
{
	if (this)
	{
		if (this->base_color)
			free(this->base_color);
		if (this->bck_tfm)
			delete_matrix(this->bck_tfm);
		if (this->fwd_tfm)
			delete_matrix(this->fwd_tfm);
		if (this->material)
			delete_material(this->material);
		free(this);
	}
}

int	close_enough(double v1, double v2)
{
	return (fabs(v1 - v2) < EPSILON);
}

vector_t * false(int *status)
{
	*status = FALSE;
	return (NULL);
}

/// @brief Delete[] Operator Overload
/// @param object_t *
void	delete_object_list(t_list *list)
{
	t_list *tmp;

	while (list)
	{
		deleteObjectBase(list->content);
		tmp = list;
		list = list->next;
		free(tmp);
	}
}