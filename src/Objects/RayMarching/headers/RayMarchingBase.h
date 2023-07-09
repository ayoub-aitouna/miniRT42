/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RayMarchingBase.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/08 19:55:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 19:55:57 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYMARCHING_H
# define RAYMARCHING_H

# include "../../headers/base.h"

# define MAX_STEPS 100

# ifndef M_EPSILON
#  define M_EPSILON 0.001
# endif
# ifndef D_S
#  define D_S 0.001
# endif
typedef double	(*sdf)(vector_t p, vector_t params);
typedef struct s_rm_object_params
{
	sdf			torus_sdf;
	vector_t	params;
}				t_rm_object_params;
object_t		*rm_object(vector_t *translation, vector_t *rotation,
					vector_t *scal, vector_t *color);
int				rm_int_test(object_t *this, ray_t *camera_ray,
					propretries_t *prop);
double			SDF(object_t *this, vector_t p, vector_t params);
double			calculat_sdf_diff(object_t *this, vector_t *normal,
					vector_t displacemnt, vector_t parms);
vector_t		get_local_normal(object_t *this, vector_t *cur_location,
					vector_t *dir_v, vector_t *params);
vector_t		*get_locatione_at_intersection(object_t *this, ray_t *bckray,
					vector_t *params, vector_t *dir_v);
object_t		*torus(vector_t *translation, vector_t *rotation,
					vector_t *scal, vector_t *color);
#endif