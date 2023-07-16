/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:50 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/ray.h"
#include "headers/types.h"
#include "lib/math/headers/libtypes.h"
#include "lib/math/headers/vectormath.h"

t_ray	*ray(t_vector *m_point1, t_vector *m_point2)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->point1 = m_point1;
	ray->point2 = m_point2;
	ray->m_lab = minus(ray->point2, ray->point1);
	return (ray);
}

/// @brief frees All memory Allocated By the Ray
/// @param  t_ray*
void	delete_ray(t_ray *this)
{
	if (this)
	{
		free(this->point1);
		free(this->point2);
		free(this->m_lab);
		free(this);
	}
}