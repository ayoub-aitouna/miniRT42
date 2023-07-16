/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GTFM_H
# define GTFM_H
# include "../../../headers/types.h"
# include "matrix.h"
# include <stdio.h>

t_matrix	*set_transform(t_vector *translation, t_vector *rotation,
				t_vector *scal);
t_ray		*apply_transform(t_ray *input_ray, t_object *this, int dirFlag);
t_vector	*apply_transform_vector(t_vector *inputVector, int dirFlag,
				t_object *this);
void		set_lineartfm(t_object *this);
t_vector	*get_norm(t_object *this, t_vector *input_vector);
t_matrix	*rotation_matrix_y(double angle);
t_matrix	*rotation_matrix_x(double angle);
t_matrix	*rotation_matrix_z(double angle);
t_matrix	*translation_matrix(t_vector *translation);
t_matrix	*scal_matrix(t_vector *scal);
#endif