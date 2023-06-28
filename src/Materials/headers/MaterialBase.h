/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialBase.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:22:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALBASE_H
# define MATERIALBASE_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

# ifndef MAX_REFLECTION_COUNT
#  define MAX_REFLECTION_COUNT 3
# endif

material_t	*new_material_base(double shininess_coefficient,
								double reflection_coefficient);
vector_t	*reflect_color(scene_t *scene, vector_t *localNormal,
				vector_t *initPoint, object_t *cur_object, ray_t *camera_ray,
				int rfc);
int			mt_cast_ray(scene_t *scene, ray_t *m_ray, propretries_t *prop,
				object_t *cur_object, object_t **c_obj);
void		delete_material(material_t *this);
#endif
