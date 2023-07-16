/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 19:36:34 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 19:36:40 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/RayMarchingBase.h"

double	calculat_sdf_diff(t_object *this, t_vector *normal,
		t_vector displacemnt, t_vector parms)
{
	t_vector	*val1;
	t_vector	*val2;
	double		result;

	val1 = minus(normal, &displacemnt);
	val2 = addition(normal, &displacemnt);
	result = (sdf(this, *val2, parms) - sdf(this, *val1, parms));
	free_list((void *[]){val1, val2}, 2);
	return (result);
}

double	sdf(t_object *this, t_vector p, t_vector params)
{
	return (((t_rm_object_params *)this->extra)->torus_sdf(p, params));
}
