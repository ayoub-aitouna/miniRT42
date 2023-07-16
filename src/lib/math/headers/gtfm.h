/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFM_H
# define GTFM_H
# include "../../../headers/types.h"
# include "matrix.h"
# include <stdio.h>

t_matrix	*set_transform(t_vector *translation, t_vector *rotation,
				t_vector *scal);
ray_t		*apply_transform(ray_t *input_ray, object_t *this, int dirFlag);
t_vector	*apply_transform_vector(t_vector *inputVector, int dirFlag,
				object_t *this);
void		set_lineartfm(object_t *this);
t_vector	*get_norm(object_t *this, t_vector *input_vector);
t_matrix	*rotation_matrix_y(double angle);
t_matrix	*rotation_matrix_x(double angle);
t_matrix	*rotation_matrix_z(double angle);
t_matrix	*translation_matrix(t_vector *translation);
t_matrix	*scal_matrix(t_vector *scal);
#endif