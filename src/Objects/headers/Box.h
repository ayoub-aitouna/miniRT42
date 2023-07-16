/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:24:16 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 07:01:59 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H
# include "Objectbase.h"

typedef struct s_box_solutions
{
	double		*u_values;
	double		*v_values;
	double		*solutions;
}				t_box_solutions;

t_object		*box(t_vector *translation, t_vector *rotation, t_vector *scal,
					t_vector *color);
t_vector		*get_face_normal(int index);
void			up_down_faces(t_vector *k, t_vector *a,
					t_box_solutions *box_solutions);
void			left_right_faces(t_vector *k, t_vector *a,
					t_box_solutions *box_solutions);
void			front_back_faces(t_vector *k, t_vector *a,
					t_box_solutions *box_solutions);
int				box_int_test(t_object *this, t_ray *camera_ray,
					t_propretries *prop);
int				get_nearest_intersection(t_box_solutions *box_solutions,
					int *index);
t_propretries	*set_box_propreties(t_object *this, t_ray *bckray,
					t_box_solutions *box_solutions, int index);
t_vector		*get_gb_normal(t_object *this, int index);
#endif