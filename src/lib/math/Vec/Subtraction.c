/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Subtraction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:49 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:47:47 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

t_vector	*minus(t_vector *target, t_vector *v)
{
	t_vector	*new;

	new = copy_vector(*target);
	new->x -= v->x;
	new->y -= v->y;
	new->z -= v->z;
	return (new);
}

t_vector	*normalized_sub(t_vector *u, t_vector *v)
{
	t_vector	*re;

	re = minus(u, v);
	normalize(re);
	return (re);
}

t_vector	*ms_minus(t_vector *target, t_vector *v, int free_at)
{
	t_vector	*result;

	result = minus(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

t_vector	*ms_normalized_sub(t_vector *u, t_vector *v, int free_at)
{
	t_vector	*re;

	re = minus(u, v);
	normalize(re);
	free_at_index(u, v, free_at);
	return (re);
}
