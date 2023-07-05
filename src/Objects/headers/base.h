/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:02 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/04 16:21:01 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECT_BASE_HPP
# define OBJECT_BASE_HPP
# include "../../Materials/headers/SimpleMaterial.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

vector_t * false(int *status);
int			close_enough(double v1, double v2);
object_t	*object_base(vector_t *translation, vector_t *rotation,
				vector_t *scal, vector_t *color);
void		deleteObjectBase(object_t *this);
void		delete_object_list(t_list *list);
#endif