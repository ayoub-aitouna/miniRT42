/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:37 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/31 22:18:19 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H
# include "../Lights/headers/pointlight.h"
# include "../Materials/headers/SimpleMaterial.h"
# include "../Objects/RayMarching/headers/Torus.h"
# include "../Objects/headers/Box.h"
# include "../Objects/headers/Cone.h"
# include "../Objects/headers/cylinder.h"
# include "../Objects/headers/plane.h"
# include "../Objects/headers/spher.h"
# include "../Objects/headers/triangle.h"
# include "../Textures/headers/Texturesimage.h"
# include "../Textures/headers/checker.h"
# include "../lib/lib.h"
# include "../lib/math/headers/matrix.h"
# include "../lib/math/headers/vectormath.h"
# include "camera.h"
# include "image.h"
# include "types.h"
#include "../parsing/headers/parsing.h"

int		cast_ray(t_ray *ray, t_scene *scene, t_propretries *c_prop,
			t_object **c_object);
void	update_values(t_propretries *c_prop, t_object **c_object,
			t_propretries *prop, t_object *cur_object);
t_scene	*scene(void *mlx, void *mlx_win, t_list *parsed_list);
t_image	*render(t_scene *scene, void *mlx, void *mlx_win);
void	deletescene(t_scene *this);
t_list	*objects(void *mlx, t_list* parsed);
void set_up_material_configurations(t_object *this, t_vector2 *rc, t_vector2 *tc, t_textures *texture);
int		check_n_set_dist(t_propretries *prop, t_ray *ray, double *min_dist);
#endif