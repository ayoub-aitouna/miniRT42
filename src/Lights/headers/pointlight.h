/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pointlight.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:35 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:22:36 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef POINT_LIGHT_H
#define POINT_LIGHT_H
#include "../../headers/types.h"
#include "../../headers/ray.h"
#include "../../lib/math/headers/vectormath.h"

light_t *new_light(vector_t *position, vector_t *color, double intensity);
int	calculatIlumination(light_t *this, vector_t *localNormal,
		vector_t *initPoint, double *intensity, vector_t *Color, scene_t *scene, object_t* cur_Object);

void delete_light(light_t *this);
void delete_light_list(t_list *list);

#endif
