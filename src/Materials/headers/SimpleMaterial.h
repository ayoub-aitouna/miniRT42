/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleMaterial.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:44 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:30 by aaitouna         ###   ########.fr       */
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

t_material	*new_simple_material(double shininess_coefficient,
				double reflection_coefficient);
t_vector	*calculat_color(t_scene *scene, t_propretries *prop,
				t_color_params params);
t_vector	*calculat_specular_color(t_scene *scene, t_propretries *prop,
				t_object *cur_object, t_ray *camera_ray);
t_vector	*calculat_diffuse_color(t_scene *scene, t_propretries *prop,
				t_object *cur_object);
double		calculat_spec_intensity(t_ray *light_ray, t_ray *camera_ray,
				t_vector *localNormal, t_object *cur_object);
t_ray		*generate_light_ray(t_light *light, t_vector *initPoint);
int			spec_int_test(t_scene *scene, t_ray *lighit_ray);
t_vector	get_curect_color(t_object *this, t_propretries *prop);
t_vector	*get_refractive_color(t_vector *color, t_scene *scene,
				t_color_params params, t_propretries *prop);
#endif
