/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:11:48 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

vector_t	*addition(vector_t *target, vector_t *v)
{
	vector_t	*new;

	new = copy_vector(*target);
	new->x += v->x;
	new->y += v->y;
	new->z += v->z;
	return (new);
}


vector_t	*ms_addition(vector_t *target, vector_t *v, int free_at)
{
	vector_t	*result;

	result = addition(target, v);
	free_at_index(target, v, free_at);
	return (result);
}