/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:19 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 19:31:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Cone.h"

int	in_range(double value, double min, double max)
{
	return (value > min && value < max);
}

void	cone_cap_intersection(vector_t p, vector_t n, cep_t propretries)
{
	propretries.t[2] = (p.z - 1) / -n.z;
	propretries.intersections[2] = ms_addition(&p, num_muliplication(&n,
				propretries.t[2]), 1);
	if (propretries.t[2] > 0.0 &&
		(sqrt(pow(propretries.intersections[2]->x, 2)
					+ pow(propretries.intersections[2]->y, 2))) < 1.0)
		propretries.valide_intersections[2] = TRUE;
	else
		propretries.t[2] = MAX_V;
}

/**
 * solve tot t;
 *	x^2 + y^2 = z^2
 *	replace x,y and z by (p<x,y,z> + t.n<x,y,z>)
 *	find t
 *	if t hase solution then the a = p+tn is the point of intersection 
 *	if t has no solution then ray does not intersect with the cone
 */
void	calulcat_cone_intersection(vector_t p, vector_t n, cep_t propretries)
{
	double	b;
	double	a;
	double	c;
	double	numsqrt;

	a = (pow(n.x, 2) + pow(n.y, 2) - pow(n.z, 2));
	b = 2 * ((p.x * n.x) + (p.y * n.y) - (p.z * n.z));
	c = (pow(p.x, 2) + pow(p.y, 2) - pow(p.z, 2));
	numsqrt = sqrt(pow(b, 2) - (4.0 * a * c));
	if (numsqrt > 0)
	{
		propretries.t[0] = (-b + numsqrt) / (2 * a);
		propretries.t[1] = (-b - numsqrt) / (2 * a);
		propretries.intersections[0] = ms_addition(&p, num_muliplication(&n,
					propretries.t[0]), 1);
		propretries.intersections[1] = ms_addition(&p, num_muliplication(&n,
					propretries.t[1]), 1);
		if (propretries.t[0] > 0 && in_range(propretries.intersections[0]->z,
				.0, 1.))
			propretries.valide_intersections[0] = TRUE;
		else
			propretries.t[0] = MAX_V;
		if (propretries.t[1] > 0 && in_range(propretries.intersections[1]->z,
				.0, 1.))
			propretries.valide_intersections[1] = TRUE;
		else
			propretries.t[1] = MAX_V;
	}
}

vector_t	*set_cone_properiesties(object_t *this, vector_t *poi,
		propretries_t *prop)
{
	vector_t	*normal_fp;
	vector_t	*m_normal;
	vector_t	*int_poi;

	int_poi = Apply_transform_vector(poi, FRWRD, this);
	normal_fp = vector(poi->x, poi->y, 0);
	m_normal = get_norm(this, normal_fp);
	normalize(m_normal);
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	free_list((void *[]){normal_fp, m_normal},
				2);
	return (int_poi);
}

int	cone_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop)
{
	ray_t		*bck_ray;
	cep_t		cone_prop;
	vector_t	n;
	vector_t	*poi;
	vector_t	*int_poi;
	int			index;

	cone_prop = (cep_t){.t = (double[]){MAX_V, MAX_V, MAX_V},
						.valide_intersections = (int[]){FALSE, FALSE, FALSE},
						.intersections = (vector_t *[]){NULL, NULL, NULL}};
	bck_ray = Apply_transform(camera_ray, this, BCKWRD);
	n = *bck_ray->m_lab;
	normalize(&n);
	calulcat_cone_intersection(*bck_ray->point1, n, (cep_t){.t = cone_prop.t,
			.intersections = cone_prop.intersections,
			.valide_intersections = cone_prop.valide_intersections});
	if (!close_enough(n.z, 0.0f))
		cone_cap_intersection(*bck_ray->point1, n, (cep_t){.t = cone_prop.t,
				.intersections = cone_prop.intersections,
				.valide_intersections = cone_prop.valide_intersections});
	else
		cone_prop.intersections[2] = NULL;
	delete_ray(bck_ray);
	if (!includes(cone_prop.valide_intersections, 3, TRUE))
	{
		free_list((void **)cone_prop.intersections, 3);
		return (FALSE);
	}
	index = min_index(cone_prop. t, 3);
	poi = copy_vector(*cone_prop.intersections[index]);
	free_list((void **)cone_prop.intersections, 3);
	if (index < 2)
	{
		int_poi = set_cone_properiesties(this, poi, prop);
		prop->int_point = *int_poi;
		free(int_poi);
		free(poi);
		return (TRUE);
	}
	if (index >= 2)
	{
		if (sqrt(pow(poi->x, 2) + pow(poi->y, 2)) >= 1.0 || close_enough(0.0,
				n.z))
		{
			free(poi);
			return (FALSE);
		}
		int_poi = set_cap_properiesties(this, poi, prop);
		prop->int_point = *int_poi;
		free(int_poi);
		free(poi);
		return (TRUE);
	}
	return (FALSE);
}

object_t	*cone(vector_t *translation, vector_t *rotation, vector_t *scal,
		vector_t *color)
{
	object_t	*cone;

	cone = object_base(translation, rotation, scal, color);
	cone->test_inter = cone_int_test;
	cone->material->reflection_coefficient = 0.6;
	cone->material->shininess_coefficient = 6;
	return (cone);
}
