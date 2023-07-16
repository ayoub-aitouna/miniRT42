/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MaterialBase.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:41 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIALBASE_H
# define MATERIALBASE_H
# include "../../Lights/headers/pointlight.h"
# include "../../Textures/headers/checker.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/scene.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

# ifndef MAX_REFLECTION_COUNT
#  define MAX_REFLECTION_COUNT 3
# endif

typedef struct ref_cast_prop
{
	object_t	*cur_object;
	object_t	**c_obj;
}				t_ref_cast_prop;

typedef struct color_params
{
	object_t	*cur_object;
	ray_t		*camera_ray;
	int			rfc;
}				t_color_params;

material_t		*new_material_base(double shininess_coefficient,
					double reflection_coefficient);
t_vector		*reflect_color(scene_t *scene, propretries_t *prop,
					t_color_params params);
int				mt_cast_ray(scene_t *scene, ray_t *m_ray, propretries_t *prop,
					t_ref_cast_prop cast_prop);
void			delete_material(material_t *this);
#endif
