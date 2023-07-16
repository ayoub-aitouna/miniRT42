/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:28 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:20 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H
# include "../lib/math/headers/libtypes.h"
# include "../lib/math/headers/vectormath.h"
# include "ray.h"
# include "types.h"

t_camera	*camera(double horizontal_size, double lenght,
				double aspect_ration);
void		set_loock_at(t_camera *this, t_vector *loockat);
void		set_up(t_camera *this, t_vector *Up);
void		set_position(t_camera *this, t_vector *position);
void		calculat_geometry(t_camera *this);
t_ray		*generate_ray(t_camera *this, double screenX, double screenY);
void		deletecamera(t_camera *this);
#endif
