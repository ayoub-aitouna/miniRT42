/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:06 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/02 17:56:10 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H
# include "base.h"
# include "cylinder.h"
int			in_range(double value, double min, double max);
void		cone_cap_intersection(vector_t p, vector_t *n, cep_t *propretries);
void		check_nd_set(cep_t *propretries, int index);
cep_t		*init_cap_prop(void);
void		calulcat_cone_intersection(vector_t p, vector_t *n,
				cep_t *propretries);
int			set_cone_properiesties(object_t *this, vector_t *poi,
				propretries_t *prop);
int			cone_int_test(object_t *this, ray_t *camera_ray,
				propretries_t *prop);
void		check_intersections(ray_t *bck_ray, vector_t *n, cep_t *cone_prop,
				propretries_t *prop);
vector_t	*normilized_copy(vector_t *v);
object_t	*cone(vector_t *translation, vector_t *rotation, vector_t *scal,
				vector_t *color);
#endif