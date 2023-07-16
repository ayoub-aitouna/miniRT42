/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refractive.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:21:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTIVE_H
# define REFRACTIVE_H
# include "MaterialBase.h"
t_vector	*refractive_color(scene_t *scene, t_color_params params,
				propretries_t *prop);
ray_t		*reflacted_ray(ray_t *camera_ray, double r, propretries_t *prop);
#endif