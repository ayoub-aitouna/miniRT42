/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:06 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H
# include "Objectbase.h"
# include "cylinder.h"
int			in_range(double value, double min, double max);
void		cone_cap_intersection(t_vector p, t_vector *n, cep_t *propretries);
cep_t		*init_cap_prop(void);
void		calulcat_cone_intersection(t_vector p, t_vector *n,
				cep_t *propretries);
int			set_cone_properiesties(object_t *this, t_vector *poi,
				propretries_t *prop);
int			cone_int_test(object_t *this, ray_t *camera_ray,
				propretries_t *prop);
void		check_intersections(ray_t *bck_ray, t_vector *n, cep_t *cone_prop,
				propretries_t *prop);
t_vector	*normilized_copy(t_vector *v);
object_t	*cone(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
#endif