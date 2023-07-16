/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 07:02:43 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "Objectbase.h"

t_object	*cylinder(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
int			cy_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop);
int			set_cap_properiesties(t_object *this, t_vector *poi, t_vector n,
				t_propretries *prop);
int			set_cylider_properiesties(t_object *this, t_vector *poi,
				t_propretries *prop);
void		calulcat_cap_intersection(t_vector p, t_vector n,
				t_cep *cylinder_prop);
void		calulcat_cylider_intersection(t_vector p, t_vector n,
				t_cep *cylinder_prop);
int			includes(int *list, int size, int value);
int			min_index(double *list, int size);
void		check_nd_set(t_cep *propretries, int index, int z_condition);
int			cylinder_intersection_points(t_ray *bck_ray, t_propretries *prop,
				t_cep *cylinder_prop);
#endif
