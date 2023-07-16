/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Objectbase.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:02 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJECTBASE_H
# define OBJECTBASE_H
# include "../../Materials/headers/SimpleMaterial.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

t_vector * false(int *status);
int			close_enough(double v1, double v2);
object_t	*object_base(t_vector *translation, t_vector *rotation,
				t_vector *scal, t_vector *color);
void		deleteObjectBase(object_t *this);
void		delete_object_list(t_list *list);
#endif