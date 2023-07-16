/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:30 by aaitouna         ###   ########.fr       */
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
	t_vector	*color;
	t_scene		*scene;
	t_object	*cur_object;
}				t_light_params;

t_light			*new_light(t_vector *position, t_vector *color,
					double intensity);
int				calculat_ilumination(t_light *this, t_propretries *prop,
					t_light_params params);

void			delete_light(t_light *this);
void			delete_light_list(t_list *list);

#endif
