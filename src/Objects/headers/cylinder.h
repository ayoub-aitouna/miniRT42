/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/03 14:35:21 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "base.h"

object_t	*cylinder(vector_t *translation, vector_t *rotation, vector_t *scal,
				vector_t *color);
int			cy_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
int			set_cap_properiesties(object_t *this, vector_t *poi, vector_t n,
				propretries_t *prop);
int			set_cylider_properiesties(object_t *this, vector_t *poi,
				propretries_t *prop);
void	calulcat_cap_intersection(vector_t p,
								vector_t n,
								cep_t *cylinder_prop);
void		calulcat_cylider_intersection(vector_t p, vector_t n,
				cep_t *cylinder_prop);
int			includes(int *list, int size, int value);
int			min_index(double *list, int size);
void		check_nd_set(cep_t *propretries, int index, int z_condition);
int	cylinder_intersection_points(ray_t *bck_ray,
									propretries_t *prop,
									cep_t *cylinder_prop);
#endif
