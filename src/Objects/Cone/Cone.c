/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:19 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:16:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Cone.h"

t_object	*cone(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	t_object	*cone;

	cone = object_base(translation, rotation, scal, color);
	cone->test_inter = cone_int_test;
	cone->material->reflection_coefficient = 0.;
	cone->material->shininess_coefficient = 6;
	return (cone);
}

int	cone_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_cep		cone_prop;
	t_vector	*n;
	t_vector	*poi;
	int			index;
	t_ray		*bck_ray;

	cone_prop = (t_cep){.t = (double []){MAX_V, MAX_V, MAX_V},
		.valide_intersections = (int []){FALSE, FALSE, FALSE},
		.intersections = (t_vector * []){NULL, NULL, NULL}};
	bck_ray = apply_transform(camera_ray, this, BCKWRD);
	n = normilized_copy(bck_ray->m_lab);
	check_intersections(bck_ray, n, &cone_prop, prop);
	if (!includes(cone_prop.valide_intersections, 3, TRUE))
		return (FALSE);
	index = min_index(cone_prop.t, 3);
	poi = copy_vector(*cone_prop.intersections[index]);
	free_list((void **)cone_prop.intersections, 3);
	if (index < 2)
		return (set_cone_properiesties(this, poi, prop));
	else
		return (set_cap_properiesties(this, poi, *n, prop));
}

void	check_intersections(t_ray *bck_ray, t_vector *n, t_cep *cone_prop,
		t_propretries *prop)
{
	calulcat_cone_intersection(*bck_ray->point1, n, cone_prop);
	if (!close_enough(n->z, 0.0f))
	{
		cone_cap_intersection(*bck_ray->point1, n, cone_prop);
		prop->uv_cords = (t_uv_cords){bck_ray->point1->x + (cone_prop->t[2]
				* n->x), bck_ray->point1->y + (cone_prop->t[2] * n->y)};
	}
	delete_ray(bck_ray);
}

t_vector	*normilized_copy(t_vector *v)
{
	t_vector	*copy;

	copy = copy_vector(*v);
	normalize(copy);
	return (copy);
}
