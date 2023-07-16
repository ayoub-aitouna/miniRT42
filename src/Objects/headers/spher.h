/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spher.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHER_H
# define SPHER_H
# include "Objectbase.h"

object_t	*create_sphere(t_vector *translation, t_vector *rotation,
				t_vector *scal, t_vector *color);
t_vector	*fs_addition(t_vector *u, t_vector *v);
double		min_t(double numsqrt, double b, int *status);
void		int_point_propreties(t_vector *poi, object_t *this,
				propretries_t *prop);
t_vector	*calculat_int_point(ray_t *bck_ray, t_vector vhat, int *status);
int			sh_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
#endif
