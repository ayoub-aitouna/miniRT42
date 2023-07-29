/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:34:50 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/29 20:18:50 by aaitouna         ###   ########.fr       */
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

void			err(char *msg);
void			check_for_parametres(char **list, t_parsing *pars);
t_list			*readfile(char *filename);
t_scene_object	*handle_line(char *line);
int				double_ptr_size(char **str);
t_vector		*vec_range_check(char **list, double max, double min);
int				f_in_range(double value, double max, double min);
t_scene_object	*handle_cy_cone(char **elements);
t_scene_object	*handle_ambient(char **elements);
t_scene_object	*handle_camera(char **elements);
t_scene_object	*handle_light(char **elements);
t_scene_object	*handle_plane(char **elements);
t_scene_object	*handle_cy_cone(char **elements);
t_scene_object	*handle_sphere(char **elements);
#endif