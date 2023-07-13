/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:47 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:12:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

vector_t	*muliplication(vector_t *target, vector_t *v)
{
	vector_t	*new;

	new = copy_vector(*target);
	new->x *= v->x;
	new->y *= v->y;
	new->z *= v->z;
	return (new);
}

vector_t	*num_muliplication(vector_t *target, double num)
{
	vector_t	*new;

	new = copy_vector(*target);
	new->x *= num;
	new->y *= num;
	new->z *= num;
	return (new);
}

vector_t	*ms_muliplication(vector_t *target, vector_t *v, int free_at)
{
	vector_t	*result;

	result = muliplication(target, v);
	free_at_index(target, v, free_at);
	return (result);
}

vector_t	*ms_num_muliplication(vector_t *target, double num)
{
	vector_t	*result;

	result = num_muliplication(target, num);
	free(target);
	return (result);
}