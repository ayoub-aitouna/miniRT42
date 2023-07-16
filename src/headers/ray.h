/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H
# include "../Lights/headers/pointlight.h"
# include "../Materials/headers/SimpleMaterial.h"
# include "../Objects/headers/Cone.h"
# include "../Objects/headers/cylinder.h"
# include "../Objects/headers/plane.h"
# include "../Objects/headers/spher.h"
# include "../Objects/headers/triangle.h"
# include "../lib/lib.h"
# include "../lib/math/headers/matrix.h"
# include "../lib/math/headers/vectormath.h"
# include "camera.h"
# include "image.h"
# include "types.h"

t_ray	*ray(t_vector *point1, t_vector *point2);
void	delete_ray(t_ray *this);
#endif