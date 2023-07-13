/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Subtraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:49 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:27:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

vector_t	*minus(vector_t *target, vector_t *v)
{
	vector_t	*new;

	new = copy_vector(*target);
	new->x -= v->x;
	new->y -= v->y;
	new->z -= v->z;
	return (new);
}

vector_t	*normalized_sub(vector_t *u, vector_t *v)
{
	vector_t	*re;

	re = minus(u, v);
	normalize(re);
	return (re);
}

vector_t	*ms_minus(vector_t *target, vector_t *v, int free_at)
{
	vector_t	*result;

	result = minus(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t	*ms_normalized_sub(vector_t *u, vector_t *v, int free_at)
{
	vector_t	*re;

	re = minus(u, v);
	normalize(re);
	free_at_index(u, v, free_at);
	return (re);
}