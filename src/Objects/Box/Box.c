/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:13:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Box.h"

t_object	*box(t_vector *translation, t_vector *rotation, t_vector *scal,
		t_vector *color)
{
	t_object	*box;

	box = object_base(translation, rotation, scal, color);
	box->test_inter = box_int_test;
	box->material->shininess_coefficient = 10.f;
	box->material->reflection_coefficient = .2;
	return (box);
}

int	box_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop)
{
	t_ray			*bckray;
	t_vector		k;
	int				index;
	t_propretries	*local_prop;
	t_box_solutions	box_solutions;

	box_solutions = (t_box_solutions){(double []){MAX_V, MAX_V, MAX_V, MAX_V,
		MAX_V, MAX_V}, (double []){0.0, 0.0, 0.0, 0.0, 0.0, 0.0},
		(double []){0.0, 0.0, 0.0, 0.0, 0.0, 0.0}};
	bckray = apply_transform(camera_ray, this, BCKWRD);
	k = *bckray->m_lab;
	normalize(&k);
	up_down_faces(&k, bckray->point1, &box_solutions);
	left_right_faces(&k, bckray->point1, &box_solutions);
	front_back_faces(&k, bckray->point1, &box_solutions);
	if (!get_nearest_intersection(&box_solutions, &index))
		return (FALSE);
	local_prop = set_box_propreties(this, bckray, &box_solutions, index);
	*prop = *local_prop;
	free(local_prop);
	return (TRUE);
}

t_propretries	*set_box_propreties(t_object *this, t_ray *bckray,
		t_box_solutions *box_solutions, int index)
{
	t_vector		*poi;
	t_vector		*m_normal;
	t_vector		*int_poi;
	t_propretries	*prop;
	t_vector		k;

	k = *bckray->m_lab;
	normalize(&k);
	prop = malloc(sizeof(t_propretries));
	poi = ms_addition(bckray->point1, num_muliplication(&k,
				box_solutions->solutions[index]), 1);
	int_poi = apply_transform_vector(poi, FRWRD, this);
	m_normal = get_gb_normal(this, index);
	prop->int_point = *int_poi;
	prop->local_normal = *m_normal;
	prop->local_color = *this->base_color;
	prop->uv_cords = (t_uv_cords){box_solutions->u_values[index],
		box_solutions->v_values[index]};
	return (prop);
}

t_vector	*get_gb_normal(t_object *this, int index)
{
	t_vector	*normal;
	t_vector	*m_normal;

	normal = get_face_normal(index);
	m_normal = get_norm(this, normal);
	free(normal);
	return (m_normal);
}

int	get_nearest_intersection(t_box_solutions *box_solutions, int *index)
{
	int		i;
	int		valide_int;
	double	t;

	*index = 0;
	valide_int = FALSE;
	t = MAX_V;
	i = 0;
	while (i < 6)
	{
		if ((box_solutions->solutions[i] < t
				&& box_solutions->solutions[i] > 0.0)
			&& fabs(box_solutions->u_values[i]) <= 1
			&& fabs(box_solutions->v_values[i]) <= 1)
		{
			valide_int = TRUE;
			*index = i;
			t = box_solutions->solutions[i];
		}
		i++;
	}
	return (valide_int);
}
