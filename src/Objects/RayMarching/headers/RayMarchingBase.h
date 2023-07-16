/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayMarchingBase.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYMARCHINGBASE_H
# define RAYMARCHINGBASE_H

# include "../../headers/Objectbase.h"

# define MAX_STEPS 100

# ifndef M_EPSILON
#  define M_EPSILON 0.001
# endif
# ifndef D_S
#  define D_S 0.001
# endif
typedef double	(*sdf)(t_vector p, t_vector params);
typedef struct s_rm_object_params
{
	sdf			torus_sdf;
	t_vector	params;
}				t_rm_object_params;
object_t		*rm_object(t_vector *translation, t_vector *rotation,
					t_vector *scal, t_vector *color);
int				rm_int_test(object_t *this, ray_t *camera_ray,
					propretries_t *prop);
double			SDF(object_t *this, t_vector p, t_vector params);
double			calculat_sdf_diff(object_t *this, t_vector *normal,
					t_vector displacemnt, t_vector parms);
t_vector		get_local_normal(object_t *this, t_vector *cur_location,
					t_vector *dir_v, t_vector *params);
t_vector		*get_locatione_at_intersection(object_t *this, ray_t *bckray,
					t_vector *params, t_vector *dir_v);
object_t		*torus(t_vector *translation, t_vector *rotation,
					t_vector *scal, t_vector *color);
#endif