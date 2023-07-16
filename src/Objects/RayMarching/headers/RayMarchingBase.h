/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayMarchingBase.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 19:32:39 by aaitouna         ###   ########.fr       */
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

typedef double	(*t_sdf)(t_vector p, t_vector params);
typedef struct s_rm_object_params
{
	t_sdf		torus_sdf;
	t_vector	params;
}				t_rm_object_params;

t_object		*rm_object(t_vector *translation, t_vector *rotation,
					t_vector *scal, t_vector *color);
int				rm_int_test(t_object *this, t_ray *camera_ray,
					t_propretries *prop);
double			sdf(t_object *this, t_vector p, t_vector params);
double			calculat_sdf_diff(t_object *this, t_vector *normal,
					t_vector displacemnt, t_vector parms);
t_vector		get_local_normal(t_object *this, t_vector *cur_location,
					t_vector *dir_v, t_vector *params);
t_vector		*get_locatione_at_intersection(t_object *this, t_ray *bckray,
					t_vector *params, t_vector *dir_v);
t_object		*torus(t_vector *translation, t_vector *rotation,
					t_vector *scal, t_vector *color);
#endif