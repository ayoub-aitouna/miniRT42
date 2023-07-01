/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 14:20:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINTLIGHT_H
# define POINTLIGHT_H
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/vectormath.h"

typedef struct light_params
{
	double		*intensity;
	vector_t	*color;
	scene_t		*scene;
	object_t	*cur_object;
}				t_light_params;

light_t			*new_light(vector_t *position, vector_t *color,
					double intensity);
int				calculat_ilumination(light_t *this, propretries_t *prop,
					t_light_params params);

void			delete_light(light_t *this);
void			delete_light_list(t_list *list);

#endif
