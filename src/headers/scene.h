/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:37 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 06:50:13 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "../Lights/headers/pointlight.h"
# include "../Materials/headers/SimpleMaterial.h"
# include "../Objects/headers/Box.h"
# include "../Objects/headers/Cone.h"
# include "../Objects/headers/cylinder.h"
# include "../Objects/headers/plane.h"
# include "../Objects/headers/spher.h"
# include "../Objects/headers/triangle.h"
# include "../Textures/headers/checker.h"
# include "../Textures/headers/image.h"
# include "../lib/lib.h"
# include "../lib/math/headers/matrix.h"
# include "../lib/math/headers/vectormath.h"
# include "camera.h"
# include "image.h"
# include "types.h"

int		cast_ray(ray_t *ray, scene_t *scene, propretries_t *c_prop,
			object_t **c_object);
void	update_values(propretries_t *c_prop, object_t **c_object,
			propretries_t *prop, object_t *cur_object);
scene_t	*Scene(void *mlx, void *mlx_win);
t_image	*Render(scene_t *scene, void *mlx, void *mlx_win);
void	deleteScene(scene_t *this);
#endif