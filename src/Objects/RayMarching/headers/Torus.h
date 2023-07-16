/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Torus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:54 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TORUS_H
# define TORUS_H
# include "RayMarchingBase.h"

object_t	*torus(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
double		torus_sdf(t_vector p, t_vector params);
int			torus_test_int(object_t *this, ray_t *camera_ray,
				propretries_t *prop);
#endif