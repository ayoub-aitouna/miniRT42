/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonousparsing.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:44:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:17:48 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONOUSPARSING_H
# define BONOUSPARSING_H
# include "../../../get_next_line/get_next_line.h"
# include "../../../headers/main.h"
# include "../../../lib/math/headers/vectormath.h"
# include "../../../parsing/headers/parsing.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

t_list			*bns_readfile(char *filename);
t_scene_object	*handle_line_bonus(char *line, t_list *list);
t_scene_object	*bns_handle_plane(char **elements);
void			hepler_bns_handle_cycone(char **elements, t_utils *utils);
t_scene_object	*bns_handle_cy_cone(char **elements);
t_scene_object	*bns_handle_sphere(char **elements);
t_scene_object	*bns_handle_torus(char **elements);
t_list			*get_bns_file_content(int fd);
#endif