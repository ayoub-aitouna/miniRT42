/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:44:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:13:54 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../../get_next_line/get_next_line.h"
# include "../../headers/main.h"
# include "../../lib/math/headers/vectormath.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct utils
{
	double			diameter;
	t_scene_object	*obj;
	char			**vec_elements;
	double			height;

}t_utils;

void			err(char *msg);
t_scene_object	*handle_plane(char **elements);
t_list			*readfile(char *filename);
t_scene_object	*handle_line(char *line, t_list *list);
int				double_ptr_size(char **str);
t_vector		*vec_range_check(char **list, double max, double min);
int				f_in_range(double value, double max, double min);
t_scene_object	*handle_ambient(char **elements);
t_scene_object	*handle_camera(char **elements);
t_scene_object	*handle_light(char **elements);
t_scene_object	*handle_cy_cone(char **elements);
t_scene_object	*handle_sphere(char **elements);
void			free_list_str(char **list);
int				check_extention(char *file_name, char *extention);
t_scene_object	*first_of(t_list *l_scene, char *type);
int				str_equal(char *s1, char *s2);
t_vector		*convert_vec_color(t_vector *color);
t_scene_object	*init_t_scene_object(void);
void			set_up_material_proprieties(char *mt_coefficient, char *texture,
					t_scene_object *obj);
void			exit_f_out_of_range(t_vector2 *vec, double max1, double max2);
void			hepler_handle_cycone(char **elements, t_utils *utils);
void			free_linkedlst(t_list *head);
void			check_for_file(char *filename);
int				equal_atleast_once(char *s1, char **list);
t_list			*get_file_content(int fd);
#endif