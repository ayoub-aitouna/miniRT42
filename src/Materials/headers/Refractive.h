/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refractive.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:21:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/04 17:35:36 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTIVE_H
# define REFRACTIVE_H
# include "MaterialBase.h"
vector_t	*refractive_color(scene_t *scene,
							t_color_params params,
							propretries_t *prop);
ray_t		*reflacted_ray(ray_t *camera_ray, double r, propretries_t *prop);
#endif