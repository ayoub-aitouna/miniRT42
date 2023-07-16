/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Refractive.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 16:21:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:59:30 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REFRACTIVE_H
# define REFRACTIVE_H
# include "MaterialBase.h"
t_vector	*refractive_color(t_scene *scene, t_color_params params,
				t_propretries *prop);
t_ray		*reflacted_ray(t_ray *camera_ray, double r, t_propretries *prop);
#endif