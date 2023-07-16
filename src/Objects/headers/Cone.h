/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:06 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 07:02:31 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
# define CONE_H
# include "Objectbase.h"
# include "cylinder.h"

int			in_range(double value, double min, double max);
void		cone_cap_intersection(t_vector p, t_vector *n, t_cep *propretries);
t_cep		*init_cap_prop(void);
void		calulcat_cone_intersection(t_vector p, t_vector *n,
				t_cep *propretries);
int			set_cone_properiesties(t_object *this, t_vector *poi,
				t_propretries *prop);
int			cone_int_test(t_object *this, t_ray *camera_ray,
				t_propretries *prop);
void		check_intersections(t_ray *bck_ray, t_vector *n, t_cep *cone_prop,
				t_propretries *prop);
t_vector	*normilized_copy(t_vector *v);
t_object	*cone(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
#endif