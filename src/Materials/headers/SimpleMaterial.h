/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleMaterial.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:44 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLEMATERIAL_H
# define SIMPLEMATERIAL_H
# include "../../headers/main.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"
# include "MaterialBase.h"
# include "Refractive.h"

material_t	*new_simple_material(double shininess_coefficient,
				double reflection_coefficient);
t_vector	*calculat_color(scene_t *scene, propretries_t *prop,
				t_color_params params);
t_vector	*calculat_specular_color(scene_t *scene, propretries_t *prop,
				object_t *cur_object, ray_t *camera_ray);
t_vector	*calculat_diffuse_color(scene_t *scene, propretries_t *prop,
				object_t *cur_object);
double		calculat_spec_intensity(ray_t *light_ray, ray_t *camera_ray,
				t_vector *localNormal, object_t *cur_object);
ray_t		*generate_light_ray(light_t *light, t_vector *initPoint);
int			spec_int_test(scene_t *scene, ray_t *lighit_ray);
t_vector	get_curect_color(object_t *this, propretries_t *prop);
t_vector	*get_refractive_color(t_vector *color, scene_t *scene,
				t_color_params params, propretries_t *prop);
#endif
