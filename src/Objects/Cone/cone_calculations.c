/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_calculations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:09:32 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/01 05:43:44 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cone.h"

/**
 * solve tot t;
 *	x^2 + y^2 = z^2
 *	replace x,y and z by (p<x,y,z> + t.n<x,y,z>)
 *	find t
 *	if t hase solution then the a = p+tn is the point of intersection
 *	if t has no solution then ray does not intersect with the cone
 */
void	calulcat_cone_intersection(t_vector p, t_vector *n, t_cep *propretries)
{
	double	b;
	double	a;
	double	c;
	double	numsqrt;

	a = (pow(n->x, 2) + pow(n->y, 2) - pow(n->z, 2));
	b = 2 * ((p.x * n->x) + (p.y * n->y) - (p.z * n->z));
	c = (pow(p.x, 2) + pow(p.y, 2) - pow(p.z, 2));
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		propretries->t[0] = (-b + numsqrt) / (2 * a);
		propretries->t[1] = (-b - numsqrt) / (2 * a);
		propretries->intersections[0] = ms_addition(&p, num_muliplication(n,
					propretries->t[0]), 1);
		propretries->intersections[1] = ms_addition(&p, num_muliplication(n,
					propretries->t[1]), 1);
		check_nd_set(propretries, 0, in_range(propretries->intersections[0]->z,
				.0, 1.));
		check_nd_set(propretries, 1, in_range(propretries->intersections[1]->z,
				.0, 1.));
	}
}

void	cone_cap_intersection(t_vector p, t_vector *n, t_cep *propretries)
{
	propretries->t[2] = (p.z - 1) / -n->z;
	propretries->intersections[2] = ms_addition(&p, num_muliplication(n,
				propretries->t[2]), 1);
	if (propretries->t[2] > 0.0 && (sqrt(pow(propretries->intersections[2]->x,
					2) + pow(propretries->intersections[2]->y, 2))) < 1.0)
		propretries->valide_intersections[2] = TRUE;
	else
		propretries->t[2] = MAX_V;
}

void	check_nd_set(t_cep *propretries, int index, int z_condition)
{
	if (propretries->t[index] > 0 && z_condition)
		propretries->valide_intersections[index] = TRUE;
	else
		propretries->t[index] = MAX_V;
}

int	set_cone_properiesties(t_object *this, t_vector *poi, t_propretries *prop)
{
	t_vector	*m_normal;
	t_vector	*int_poi;

	int_poi = apply_transform_vector(poi, FRWRD, this);
	m_normal = get_norm(this, this->normal);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->int_point = *int_poi;
	prop->uv_cords = (t_uv_cords){atan2(poi->x, poi->y), poi->z};
	free_list((void *[]){m_normal, int_poi, poi}, 3);
	return (TRUE);
}

int	in_range(double value, double min, double max)
{
	return (value > min && value < max);
}
