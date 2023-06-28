/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:09 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:23:10 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CYLINDER_H
# define CYLINDER_H
# include "base.h"

object_t	*cylinder(vector_t *translation, vector_t *rotation, vector_t *scal,
				vector_t *color);
int			cy_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
vector_t	*set_cap_properiesties(object_t *this, vector_t *poi,
				propretries_t *prop);
vector_t	*set_cylider_properiesties(object_t *this, vector_t *poi,
				vector_t *local_normal, vector_t *local_color);
void		calulcat_cap_intersection(double *t, vector_t p, vector_t n,
				vector_t **intersections, int *valide_intersections);
void		calulcat_cylider_intersection(double *t, vector_t p, vector_t n,
				vector_t **intersections, int *valide_intersections);
int			includes(int *list, int size, int value);
int			min_index(double *list, int size);
#endif
