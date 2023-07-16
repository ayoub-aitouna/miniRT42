/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:40 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "../lib/lib.h"
# include <math.h>
# include <stdlib.h>

typedef struct Object		object_t;
typedef struct material		material_t;
typedef struct Propretries	propretries_t;
typedef struct s_textures	t_textures;
typedef struct color_params	t_color_params;

typedef struct s_data
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						line_length;
	int						endian;
}							t_data;

typedef struct ray
{
	t_vector				*point1;
	t_vector				*point2;
	t_vector				*m_lab;
}							ray_t;

typedef int					(*test_intersection)(object_t *this,
						struct ray *ray, propretries_t *prop);

typedef struct Object
{
	t_matrix				*fwd_tfm;
	t_matrix				*bck_tfm;
	t_matrix				*lineartfm;
	t_vector				*base_color;
	test_intersection		test_inter;
	material_t				*material;
	t_textures				*textures;
	void					*extra;
}							object_t;

typedef struct Light
{
	t_vector				*base_color;
	t_vector				*position;
	double					m_intensity;
}							light_t;

typedef struct camera
{
	t_vector				*position;
	t_vector				*loockat;
	t_vector				*up;
	t_vector				*screen_u;
	t_vector				*screen_v;
	t_vector				*screen_center;
	double					lenght;
	double					horizontal_size;
	double					aspect_ration;
}							camera_t;

typedef struct Scene
{
	t_list					*m_object_list;
	t_list					*m_light_list;
	camera_t				*m_camera;
	t_vector				ambient_light_factor;
}							scene_t;

typedef struct cylinder_equations_Propretries
{
	t_vector				**intersections;
	int						*valide_intersections;
	double					*t;
}							cep_t;

typedef t_vector			*(*compute_color)(scene_t *scene,
								propretries_t *prop, t_color_params params);

typedef struct material
{
	double					shininess_coefficient;
	double					reflection_coefficient;
	double					transparency_coefficient;
	double					reflactive_index;
	compute_color			calculat_color;

}							material_t;

typedef struct uv_cords
{
	double					u;
	double					v;
}							t_uv_cords;

typedef struct Propretries
{
	t_vector				local_color;
	t_vector				local_normal;
	t_vector				int_point;
	t_vector				poi;
	t_uv_cords				uv_cords;
}							propretries_t;
typedef t_vector			*(*get_color_function)(t_textures *this,
								t_uv_cords cords);
typedef struct s_textures
{
	t_vector				color_1;
	t_vector				color_2;
	t_matrix				*tfm;
	t_data					*img;
	int						img_width;
	int						img_height;
	get_color_function		get_color;
}							t_textures;

#endif
