/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:50 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/18 00:32:23 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/ray.h"
#include "headers/types.h"
#include "headers/scene.h"
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

int	check_n_set_dist(t_propretries *prop, t_ray *ray, double *min_dist)
{
	double	dist;

	dist = vector_distance(&prop->int_point, ray->point1);
	if (dist < *min_dist)
	{
		*min_dist = dist;
		return (TRUE);
	}
	return (FALSE);
}

int	cast_ray(t_ray *ray, t_scene *scene, t_propretries *c_prop,
		t_object **c_object)
{
	int				found_int;
	t_list			*tmp;
	t_propretries	prop;
	double			min_dist;

	found_int = 0;
	tmp = scene->m_object_list;
	min_dist = 1e6;
	while (tmp)
	{
		if (((t_object *)tmp->content) != NULL)
		{
			if (((t_object *)tmp->content)
				->test_inter(((t_object *)tmp->content),
					ray, &prop))
			{
				found_int = 1;
				if (check_n_set_dist(&prop, ray, &min_dist))
					update_values(c_prop, c_object, &prop,
						((t_object *)tmp->content));
			}
		}
		tmp = tmp->next;
	}
	return (found_int);
}

void	update_values(t_propretries *c_prop, t_object **c_object,
		t_propretries *prop, t_object *cur_object)
{
	*c_prop = *prop;
	*c_object = cur_object;
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
