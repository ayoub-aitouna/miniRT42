/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/26 10:34:48 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

double	vector_lenght2(t_vector v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double	vector_lenght(t_vector v)
{
	return (sqrtf(vector_lenght2(v)));
}

double	dot(t_vector v, t_vector u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

t_vector	*cross(t_vector v, t_vector u)
{
	return (vector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y
			* u.x));
}

void	print_vector(t_vector v)
{
	printf("(%.3f, %.3f, %.3f)\n", v.x, v.y, v.z);
}
