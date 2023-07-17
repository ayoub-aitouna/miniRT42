/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_calculations.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:10:25 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:11:24 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/cylinder.h"

/**
 *
 * solve tot t;
 * t^2.a + t.b + p = 0;
 * a = (nx^2 + ny^2)
 * b = (2.px.nx + 2.py.ny)
 * c = (py^2 + px^2 - r^2)
 */
void	calulcat_cylider_intersection(t_vector p, t_vector n,
		t_cep *cylinder_prop)
{
	double	b;
	double	a;
	double	c;
	double	numsqrt;

	a = (pow(n.x, 2) + pow(n.y, 2));
	b = 2 * ((p.x * n.x) + (p.y * n.y));
	c = (pow(p.x, 2) + pow(p.y, 2) - 1.0);
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		cylinder_prop->t[0] = (-b + numsqrt) / (2 * a);
		cylinder_prop->t[1] = (-b - numsqrt) / (2 * a);
		cylinder_prop->intersections[0] = ms_addition(&p, num_muliplication(&n,
					cylinder_prop->t[0]), 1);
		cylinder_prop->intersections[1] = ms_addition(&p, num_muliplication(&n,
					cylinder_prop->t[1]), 1);
		check_nd_set(cylinder_prop, 0,
			fabs(cylinder_prop->intersections[0]->z) < 1.0);
		check_nd_set(cylinder_prop, 1,
			fabs(cylinder_prop->intersections[1]->z) < 1.0);
	}
}

void	calulcat_cap_intersection(t_vector p, t_vector n, t_cep *cylinder_prop)
{
	cylinder_prop->t[2] = (p.z - 1) / -n.z;
	cylinder_prop->t[3] = (p.z + 1) / -n.z;
	cylinder_prop->intersections[2] = ms_addition(&p, num_muliplication(&n,
				cylinder_prop->t[2]), 1);
	cylinder_prop->intersections[3] = ms_addition(&p, num_muliplication(&n,
				cylinder_prop->t[3]), 1);
	if (cylinder_prop->t[2] > 0.0
		&& (sqrt(pow(cylinder_prop->intersections[2]->x, 2)
				+ pow(cylinder_prop->intersections[2]->y, 2))) < 1.0)
		cylinder_prop->valide_intersections[2] = TRUE;
	else
		cylinder_prop->t[2] = MAX_V;
	if (cylinder_prop->t[3] > 0.0
		&& sqrt(pow(cylinder_prop->intersections[3]->x, 2)
			+ pow(cylinder_prop->intersections[3]->y, 2)) < 1.0)
		cylinder_prop->valide_intersections[3] = TRUE;
	else
		cylinder_prop->t[3] = MAX_V;
}

int	min_index(double *list, int size)
{
	int		i;
	int		index;
	double	min;

	i = 0;
	index = 0;
	if (size < 0 || !list)
		return (0);
	min = list[0];
	while (i < size)
	{
		if (min > list[i])
		{
			index = i;
			min = list[i];
		}
		i++;
	}
	return (index);
}

int	includes(int *list, int size, int value)
{
	int	i;

	if (!list)
		return (-1);
	i = 0;
	while (i < size)
	{
		if (list[i] == value)
			return (value);
		i++;
	}
	return (0);
}
