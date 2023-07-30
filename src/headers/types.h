/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:40 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/30 02:48:15 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H
# include "../lib/lib.h"
# include <math.h>
# include <stdlib.h>

typedef struct Object		t_object;
typedef struct material		t_material;
typedef struct Propretries	t_propretries;
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
}							t_ray;

typedef int					(*t_test_intersection)(t_object *this,
						struct ray *ray, t_propretries *prop);

typedef struct Object
{
	t_matrix				*fwd_tfm;
	t_matrix				*bck_tfm;
	t_matrix				*lineartfm;
	t_vector				*base_color;
	t_test_intersection		test_inter;
	t_material				*material;
	t_textures				*textures;
	void					*extra;
}							t_object;

typedef struct Light
{
	t_vector				*base_color;
	t_vector				*position;
	double					m_intensity;
}							t_light;

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
}							t_camera;

typedef struct Scene
{
	t_list					*m_object_list;
	t_list					*m_light_list;
	t_camera				*m_camera;
	t_vector				ambient_light_factor;
}							t_scene;

typedef struct cylinder_equations_Propretries
{
	t_vector				**intersections;
	int						*valide_intersections;
	double					*t;
}							t_cep;

typedef t_vector			*(*t_compute_color)(t_scene *scene,
								t_propretries *prop, t_color_params params);

typedef struct material
{
	double					shininess_coefficient;
	double					reflection_coefficient;
	double					transparency_coefficient;
	double					reflactive_index;
	t_compute_color			calculat_color;

}							t_material;

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
}							t_propretries;
typedef t_vector			*(*t_get_color_function)(t_textures *this,
								t_uv_cords cords);

typedef struct s_txtr_img
{
	t_data					*img;
	int						img_width;
	int						img_height;
}							t_txtr_img;

typedef struct s_textures
{
	t_vector				color_1;
	t_vector				color_2;
	t_matrix				*tfm;
	t_txtr_img				*txtr_img;
	t_txtr_img				*surface_hieght_info;
	t_get_color_function	get_color;
	t_get_color_function	get_surface_hieght;
}							t_textures;

typedef enum TextureType
{
	NON = -1,
	CHECKBOARD = 0,
	BUMPMAPTEXTURE = 1
}							T_TextureType;

typedef struct s_scene_object
{
	char					*type;
	t_vector				*position;
	t_vector				*color;
	t_vector				*normal;
	t_vector				*reflection_pr;
	t_vector				*scal;
	double					intensity;
	double					field_of_view;
	T_TextureType			texture_type;
	char					*Texture_path;

}							t_scene_object;

typedef struct k
{
	char **A;
	char **C;
	char **L;
	char **pl;
	char **sp;
	char **cy;

}							t_parsing;

#endif
