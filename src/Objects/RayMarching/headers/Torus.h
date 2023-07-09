/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Torus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:54 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 19:55:55 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TORUS_H
# define TORUS_H
# include "RayMarchingBase.h"

object_t	*torus(vector_t *translation, vector_t *rotation, vector_t *scal,
				vector_t *color);
double		torus_sdf(vector_t p, vector_t params);
int			torus_test_int(object_t *this, ray_t *camera_ray,
				propretries_t *prop);
#endif