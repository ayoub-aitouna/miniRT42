/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   box_faces.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 22:07:26 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:07:48 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/Box.h"

void	up_down_faces(t_vector *k, t_vector *a, t_box_solutions *box_solutions)
{
	if (!close_enough(k->z, 0.f))
	{
		box_solutions->solutions[0] = (a->z - 1.0) / -k->z;
		box_solutions->solutions[1] = (a->z + 1.0) / -k->z;
		box_solutions->u_values[0] = a->x + k->x * box_solutions->solutions[0];
		box_solutions->v_values[0] = a->y + k->y * box_solutions->solutions[0];
		box_solutions->u_values[1] = a->x + k->x * box_solutions->solutions[1];
		box_solutions->v_values[1] = a->y + k->y * box_solutions->solutions[1];
	}
}

void	left_right_faces(t_vector *k, t_vector *a,
		t_box_solutions *box_solutions)
{
	if (!close_enough(k->y, 0.f))
	{
		box_solutions->solutions[4] = (a->y + 1) / -k->y;
		box_solutions->solutions[5] = (a->y - 1) / -k->y;
		box_solutions->u_values[4] = a->x + k->x * box_solutions->solutions[4];
		box_solutions->v_values[4] = a->z + k->z * box_solutions->solutions[4];
		box_solutions->u_values[5] = a->x + k->x * box_solutions->solutions[5];
		box_solutions->v_values[5] = a->z + k->z * box_solutions->solutions[5];
	}
}

void	front_back_faces(t_vector *k, t_vector *a,
		t_box_solutions *box_solutions)
{
	if (!close_enough(k->x, 0.f))
	{
		box_solutions->solutions[2] = (a->x + 1.0) / -k->x;
		box_solutions->solutions[3] = (a->x - 1.0) / -k->x;
		box_solutions->u_values[2] = a->z + k->z * box_solutions->solutions[2];
		box_solutions->v_values[2] = a->y + k->y * box_solutions->solutions[2];
		box_solutions->u_values[3] = a->z + k->z * box_solutions->solutions[3];
		box_solutions->v_values[3] = a->y + k->y * box_solutions->solutions[3];
	}
}

t_vector	*get_face_normal(int index)
{
	if (index == 0)
		return (vector(0, 0, 1));
	if (index == 1)
		return (vector(0, 0, -1));
	if (index == 2)
		return (vector(-1, 0, 0));
	if (index == 3)
		return (vector(1, 0, 0));
	if (index == 4)
		return (vector(0, -1, 0));
	if (index == 5)
		return (vector(0, 1, 0));
	return (NULL);
}
