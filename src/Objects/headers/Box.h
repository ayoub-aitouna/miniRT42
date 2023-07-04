/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:24:16 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/03 17:23:30 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H
# include "base.h"

typedef struct s_box_solutions
{
	double		*u_values;
	double		*v_values;
	double		*solutions;
}				t_box_solutions;

object_t		*box(vector_t *translation, vector_t *rotation, vector_t *scal,
					vector_t *color);
vector_t		*get_face_normal(int index);
void			up_down_faces(vector_t *k, vector_t *a,
					t_box_solutions *box_solutions);
void			left_right_faces(vector_t *k, vector_t *a,
					t_box_solutions *box_solutions);
void			front_back_faces(vector_t *k, vector_t *a,
					t_box_solutions *box_solutions);
int				box_int_test(object_t *this, ray_t *camera_ray,
					propretries_t *prop);
int	get_nearest_intersection(t_box_solutions *box_solutions,
								int *index);
propretries_t	*set_box_propreties(object_t *this, ray_t *bckray,
					t_box_solutions *box_solutions, int index);
vector_t		*get_gb_normal(object_t *this, int index);
#endif