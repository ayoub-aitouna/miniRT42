/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:40 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 05:29:09 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef M_TYPES_H
# define M_TYPES_H
# include "../lib/lib.h"
# include <math.h>
# include <stdlib.h>

typedef struct Object				object_t;
typedef struct material				material_t;
typedef struct Propretries			propretries_t;
typedef struct s_checker_textures	t_checker_textures;

typedef struct s_data
{
	void							*img;
	char							*addr;
	int								bits_per_pixel;
	int								line_length;
	int								endian;
}									t_data;

typedef struct ray
{
	vector_t						*point1;
	vector_t						*point2;
	vector_t						*m_lab;
}									ray_t;

typedef int (*test_intersection)(object_t *this,
									struct ray *ray,
									propretries_t *prop);

typedef struct Object
{
	matrix_t						*fwd_tfm;
	matrix_t						*bck_tfm;
	matrix_t						*lineartfm;
	vector_t						*base_color;
	test_intersection				test_inter;
	material_t						*material;
	t_checker_textures				*textures;
}									object_t;

typedef struct Light
{
	vector_t						*base_color;
	vector_t						*position;
	double							m_intensity;
}									light_t;

typedef struct camera
{
	vector_t						*position;
	vector_t						*loockat;
	vector_t						*up;
	vector_t						*screen_u;
	vector_t						*screen_v;
	vector_t						*screen_center;
	double							lenght;
	double							horizontal_size;
	double							aspect_ration;
}									camera_t;

typedef struct Scene
{
	t_list							*m_object_list;
	t_list							*m_light_list;
	camera_t						*m_camera;
	vector_t						ambient_light_factor;
}									scene_t;

typedef struct cylinder_equations_Propretries
{
	vector_t						**intersections;
	int								*valide_intersections;
	double							*t;
}									cep_t;

typedef vector_t	*(*compute_color)(scene_t *scene,
									propretries_t *prop,
									object_t *cur_object,
									ray_t *camera_ray,
									int rfc);

typedef struct material
{
	double							shininess_coefficient;
	double							reflection_coefficient;
	compute_color					calculat_color;

}									material_t;

typedef struct uv_cords
{
	double							u;
	double							v;
}									t_uv_cords;

typedef struct Propretries
{
	vector_t						local_color;
	vector_t						local_normal;
	vector_t						int_point;
	t_uv_cords						uv_cords;
}									propretries_t;
typedef vector_t	*(*get_color_function)(t_checker_textures *this,
										t_uv_cords cords);
typedef struct s_checker_textures
{
	vector_t						color_1;
	vector_t						color_2;
	matrix_t						*tfm;
	t_data							*img;
	int								img_width;
	int								img_height;
	get_color_function				get_color;
}									t_checker_textures;

#endif
