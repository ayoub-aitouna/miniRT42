/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VecMath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:13:03 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:49:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

/**
 * r = l - 2(l.n).n
 * r & l & n : are vectors
 */
t_vector	*reflection_vector(t_vector *l, t_vector *n)
{
	t_vector	*r;
	double		ln;

	ln = dot(*l, *n);
	r = ms_minus(l, num_muliplication(n, 2 * ln), 1);
	normalize(r);
	return (r);
}

double	vector_distance(t_vector *u, t_vector *v)
{
	t_vector	*result;
	double		distance;

	distance = 0.0f;
	result = minus(u, v);
	distance = vector_lenght(*result);
	free(result);
	return (distance);
}

t_vector	*from_mt_to_vt(t_matrix mt)
{
	if (mt.cols != 3 || mt.rows != 1)
		return (NULL);
	return (vector(mt.matrix[0][0], mt.matrix[0][1], mt.matrix[0][2]));
}
