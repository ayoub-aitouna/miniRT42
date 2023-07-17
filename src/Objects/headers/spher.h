/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spher.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 22:16:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHER_H
# define SPHER_H
# include "Objectbase.h"
# include <math.h>

t_object	*create_sphere(t_vector *translation, t_vector *rotation,
				t_vector *scal, t_vector *color);
t_vector	*fs_addition(t_vector *u, t_vector *v);
double		min_t(double numsqrt, double b, int *status);
void		int_point_propreties(t_vector *poi, t_object *this,
				t_propretries *prop);
t_vector	*calculat_int_point(t_ray *bck_ray, t_vector vhat, int *status);
int			sh_int_test(t_object *this, t_ray *camera_ray, t_propretries *prop);
void		calculat_uv(t_propretries *prop, t_vector *poi);
#endif
