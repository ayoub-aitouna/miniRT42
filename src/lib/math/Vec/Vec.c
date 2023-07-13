/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vec.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:13:27 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

double vector_lenght2(vector_t v)
{
	return (pow(v.x, 2) + pow(v.y, 2) + pow(v.z, 2));
}

double vector_lenght(vector_t v)
{
	return (sqrtf(vector_lenght2(v)));
}

double dot(vector_t v, vector_t u)
{
	return (v.x * u.x + v.y * u.y + v.z * u.z);
}

vector_t *cross(vector_t v, vector_t u)
{
	return (vector(v.y * u.z - v.z * u.y, v.z * u.x - v.x * u.z, v.x * u.y - v.y * u.x));
}

void print_vector(vector_t v)
{
	printf("| %f, %f, %f |\n", v.x, v.y, v.z);
}
