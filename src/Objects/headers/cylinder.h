/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "Objectbase.h"

object_t	*cylinder(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
int			cy_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
int			set_cap_properiesties(object_t *this, t_vector *poi, t_vector n,
				propretries_t *prop);
int			set_cylider_properiesties(object_t *this, t_vector *poi,
				propretries_t *prop);
void	calulcat_cap_intersection(t_vector p,
								t_vector n,
								cep_t *cylinder_prop);
void		calulcat_cylider_intersection(t_vector p, t_vector n,
				cep_t *cylinder_prop);
int			includes(int *list, int size, int value);
int			min_index(double *list, int size);
void		check_nd_set(cep_t *propretries, int index, int z_condition);
int	cylinder_intersection_points(ray_t *bck_ray,
									propretries_t *prop,
									cep_t *cylinder_prop);
#endif
