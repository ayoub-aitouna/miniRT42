/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SimpleMaterial.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:44 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 13:12:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIMPLEMATERIAL_H
# define SIMPLEMATERIAL_H
# include "../../headers/main.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"
# include "MaterialBase.h"

material_t	*new_simple_material(double shininess_coefficient,
								double reflection_coefficient);
vector_t	*calculat_color(scene_t *scene, propretries_t *prop,
				object_t *cur_object, ray_t *camera_ray, int rfc);
vector_t	*Calculat_specularColor(scene_t *scene, vector_t *localNormal,
				vector_t *initPoint, object_t *cur_object, ray_t *camera_ray);
vector_t	*CalculatDiffuseColor(scene_t *scene, propretries_t *prop,
				object_t *cur_object);
#endif
