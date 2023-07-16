/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Torus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:54 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TORUS_H
# define TORUS_H
# include "RayMarchingBase.h"

t_object	*torus(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
double		torus_sdf(t_vector p, t_vector params);
int			torus_test_int(t_object *this, t_ray *camera_ray,
				t_propretries *prop);
#endif