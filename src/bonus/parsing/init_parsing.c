/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:27:52 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 04:34:26 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/bonousparsing.h"

t_scene_object	*bsn_handle_light(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elemts;

	obj = init_t_scene_object();
	if (!obj)
		return (NULL);
	if (double_ptr_size(elements) != 4)
		err("error in args\n");
	obj->type = ft_strdup(elements[0]);
	vec_elemts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elemts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elemts[0]), atof(vec_elemts[1]),
			atof(vec_elemts[2]));
	obj->intensity = atof(elements[2]);
	free_list_str(vec_elemts);
	f_in_range(obj->intensity, 1, 0);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("Light color out of range. \n");
	return (obj);
}

t_scene_object	*handle_line_bonus(char *line, t_list *list)
{
	char			**splited;
	t_scene_object	*object;

	object = NULL;
	splited = ft_split(line, ' ');
	if (equal_atleast_once(splited[0], (char *[]){"A", "C", NULL})
		&& (first_of(list, splited[0]) != NULL))
		err("Element Duplicated \n");
	if (ft_strncmp(splited[0], "A", ft_strlen(splited[0])) == 0)
		object = handle_ambient(splited);
	if (ft_strncmp(splited[0], "C", ft_strlen(splited[0])) == 0)
		object = handle_camera(splited);
	if (ft_strncmp(splited[0], "L", ft_strlen(splited[0])) == 0)
		object = handle_light(splited);
	if (ft_strncmp(splited[0], "cy", ft_strlen(splited[0])) == 0
		|| ft_strncmp(splited[0], "co", ft_strlen(splited[0])) == 0)
		object = bns_handle_cy_cone(splited);
	if (ft_strncmp(splited[0], "sp", ft_strlen(splited[0])) == 0)
		object = bns_handle_sphere(splited);
	if (ft_strncmp(splited[0], "pl", ft_strlen(splited[0])) == 0)
		object = bns_handle_plane(splited);
	if (ft_strncmp(splited[0], "torus", ft_strlen(splited[0])) == 0)
		object = bns_handle_torus(splited);
	free_list_str(splited);
	return (object);
}
