/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:50 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/28 00:38:56 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/ray.h"
#include "headers/types.h"
#include "lib/math/headers/types.h"
#include "lib/math/headers/vectormath.h"

ray_t	*ray(vector_t *m_point1, vector_t *m_point2)
{
	ray_t	*ray;

	ray = malloc(sizeof(ray_t));
	ray->point1 = m_point1;
	ray->point2 = m_point2;
	ray->m_lab = minus(ray->point2, ray->point1);
	return (ray);
}

/// @brief frees All memory Allocated By the Ray
/// @param  ray_t*
void	delete_ray(ray_t *this)
{
	if (this)
	{
		free(this->point1);
		free(this->point2);
		free(this->m_lab);
		free(this);
	}
}