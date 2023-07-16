/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:09:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:47:28 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

t_vector	*addition(t_vector *target, t_vector *v)
{
	t_vector	*new;

	new = copy_vector(*target);
	new->x += v->x;
	new->y += v->y;
	new->z += v->z;
	return (new);
}

t_vector	*ms_addition(t_vector *target, t_vector *v, int free_at)
{
	t_vector	*result;

	result = addition(target, v);
	free_at_index(target, v, free_at);
	return (result);
}
