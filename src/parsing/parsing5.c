/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:30:30 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/31 19:35:44 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

t_scene_object	*handle_plane(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elemts;

	obj = init_t_scene_object();
	if (!obj)
		err("Error\n");
	if (double_ptr_size(elements) != 6)
		err("error in args\n");
	obj->type = ft_strdup(elements[0]);
	vec_elemts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elemts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elemts[0]), atof(vec_elemts[1]),
			atof(vec_elemts[2]));
	free_list_str(vec_elemts);
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("out of range\n");
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	set_up_material_proprieties(ft_split(elements[4], ','), elements[5], obj);
	return (obj);
}

t_scene_object	*handle_cy_cone(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elements;
	double			height;
	double			diameter;

	obj = init_t_scene_object();
	if (!obj || double_ptr_size(elements) != 8)
		err("Error \n");
	obj->type = ft_strdup(elements[0]);
	vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elements) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elements[0]), atof(vec_elements[1]),
			atof(vec_elements[2]));
	free_list_str(vec_elements);
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("out of range\n");
	diameter = atof(elements[3]);
	height = atof(elements[4]);
	if (ft_strncmp(elements[0], "cy", ft_strlen(elements[0])) == 0)
		obj->scal = vector(diameter / 2, diameter / 2, height / 2);
	else
		obj->scal = vector(diameter / 2, diameter / 2, height);
	obj->color = vec_range_check(ft_split(elements[5], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	set_up_material_proprieties(ft_split(elements[6], ','), elements[7], obj);
	return (obj);
}

t_scene_object	*handle_sphere(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elements;
	double			diameter;
	double			radius;

	obj = init_t_scene_object();
	if (!obj)
		err("Error\n");
	if (double_ptr_size(elements) != 6)
		err("2 error in args\n");
	obj->type = ft_strdup(elements[0]);
	vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elements) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elements[0]), atof(vec_elements[1]),
			atof(vec_elements[2]));
	free_list_str(vec_elements);
	diameter = atof(elements[2]);
	radius = diameter / 2;
	obj->scal = vector(radius, radius, radius);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	set_up_material_proprieties(ft_split(elements[4], ','), elements[5], obj);
	return (obj);
}

t_list	*readfile(char *filename)
{
	t_scene_object	*node_content;
	char			*line;
	t_list			*list;
	int				fd;

	list = NULL;
	if (!check_extention(filename, ".rt"))
		err("invalide Extention !!");
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err("failed to open file\n");
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		node_content = handle_line(line, list);
		if (!node_content)
			err("Elemet no recognized \n");
		push_back(&list, ft_lstnew(node_content));
		free(line);
	}
	if (!first_of(list, "C") || !first_of(list, "A") || !first_of(list, "L"))
		err("must be at least on Light Source & Camera & Ambient Light \n");
	return (list);
}
