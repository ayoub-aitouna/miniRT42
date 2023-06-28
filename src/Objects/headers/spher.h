/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spher.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:14 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:23:15 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHER_H
# define SPHER_H
# include "base.h"

object_t	*create_sphere(vector_t *translation, vector_t *rotation,
				vector_t *scal, vector_t *color);
vector_t	*fs_addition(vector_t *u, vector_t *v);
double		min_t(double numsqrt, double b, int *status);
void		int_point_propreties(vector_t *poi, object_t *this,
				propretries_t *prop);
vector_t	*calculat_int_point(ray_t *bck_ray, vector_t vhat, int *status);
int			sh_int_test(object_t *this, ray_t *camera_ray, propretries_t *prop);
#endif
