/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:47 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:47:39 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

t_vector	*muliplication(t_vector *target, t_vector *v)
{
	t_vector	*new;

	new = copy_vector(*target);
	new->x *= v->x;
	new->y *= v->y;
	new->z *= v->z;
	return (new);
}

t_vector	*num_muliplication(t_vector *target, double num)
{
	t_vector	*new;

	new = copy_vector(*target);
	new->x *= num;
	new->y *= num;
	new->z *= num;
	return (new);
}

t_vector	*ms_muliplication(t_vector *target, t_vector *v, int free_at)
{
	t_vector	*result;

	result = muliplication(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

t_vector	*ms_num_muliplication(t_vector *target, double num)
{
	t_vector	*result;

	result = num_muliplication(target, num);
	free(target);
	return (result);
}
