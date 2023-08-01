/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:21 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/31 21:59:20 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

t_vector	*vector(double x, double y, double z)
{
	t_vector	*vector;

	vector = malloc(sizeof(t_vector));
	vector->x = x;
	vector->y = y;
	vector->z = z;
	return (vector);
}

t_vector2	*vec2(double x, double y)
{
	t_vector2	*vec;

	vec = malloc(sizeof(t_vector2));
	vec->x = x;
	vec->y = y;
	return (vec);
}

t_vector	*copy_vector(t_vector v)
{
	return (vector(v.x, v.y, v.z));
}

t_vector	*normalized(t_vector *v)
{
	t_vector	*n_v;

	n_v = copy_vector(*v);
	normalize(n_v);
	return (n_v);
}

double	normalize(t_vector *v)
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
