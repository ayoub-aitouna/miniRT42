/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:14:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

vector_t	*vector(double x, double y, double z)
{
	vector_t	*vector;

	vector = malloc(sizeof(vector_t));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

vector_t	*copy_vector(vector_t v)
{
	return (vector(v.x, v.y, v.z));
}

vector_t	*normalized(vector_t *v)
{
	vector_t	*n_v;

	n_v = copy_vector(*v);
	normalize(n_v);
	return (n_v);
}

double	normalize(vector_t *v)
{
	double	l;

	l = vector_lenght(*v);
	v->x /= l;
	v->y /= l;
	v->z /= l;
	return (l);
}

void	free_at_index(void *ptr1, void *ptr2, int index)
{
	if (index == 0 || index == 2)
		free(ptr1);
	if (index == 1 || index == 2)
		free(ptr2);
}
