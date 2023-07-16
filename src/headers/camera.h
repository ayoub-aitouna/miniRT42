/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../lib/math/headers/libtypes.h"
# include "../lib/math/headers/vectormath.h"
# include "ray.h"
# include "types.h"

camera_t	*camera(double horizontal_size, double lenght,
				double aspect_ration);
void		set_loock_at(camera_t *this, t_vector *loockat);
void		set_up(camera_t *this, t_vector *Up);
void		set_position(camera_t *this, t_vector *position);
void		calculat_geometry(camera_t *this);
ray_t		*generate_ray(camera_t *this, double screenX, double screenY);
void		deletecamera(camera_t *this);
#endif
