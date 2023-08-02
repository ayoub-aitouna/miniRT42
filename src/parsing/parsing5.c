/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:30:30 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/01 23:12:37 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

t_scene_object	*handle_plane(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elemts;

	obj = init_t_scene_object();
	if (!obj)
		err("Error \n");
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
		err("Plan Normal out of range\n");
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("Plane Color out of range\n");
	set_up_material_proprieties(elements[4], elements[5], obj);
	return (obj);
}

void	hepler_handle_cycone(char **elements, t_utils *utils)
{
	utils->obj = init_t_scene_object();
	if (!utils->obj || double_ptr_size(elements) != 8)
		err("Error \n");
	utils->obj->type = ft_strdup(elements[0]);
	utils->vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(utils->vec_elements) != 3)
		err("error in args\n");
	utils->obj->position = vector(atof(utils->vec_elements[0]),
			atof(utils->vec_elements[1]), atof(utils->vec_elements[2]));
	free_list_str(utils->vec_elements);
	utils->obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
}

t_scene_object	*handle_cy_cone(char **elements)
{
	t_utils		utils;
	
	hepler_handle_cycone(elements, &utils);
	if (!utils.obj->normal)
		err("Cone/Cylinder Normal out of range\n");
	utils.diameter = atof(elements[3]);
	utils.height = atof(elements[4]);
	if (ft_strncmp(elements[0], "cy", ft_strlen(elements[0])) == 0)
		utils.obj->scal = vector(utils.diameter / 2, utils.diameter / 2,
				utils.height / 2);
	else
		utils.obj->scal = vector(utils.diameter / 2, utils.diameter / 2,
				utils.height);
	utils.obj->color = vec_range_check(ft_split(elements[5], ','), 255, 0);
	if (!utils.obj->color)
		err("Cone/Cylinder Color out of range\n");
	set_up_material_proprieties(elements[6], elements[7], utils.obj);
	return (utils.obj);
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
		err("Shpere has more then allowed elements. \n");
	obj->type = ft_strdup(elements[0]);
	vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elements) != 3)
		err("position vector invalide. \n");
	obj->position = vector(atof(vec_elements[0]), atof(vec_elements[1]),
			atof(vec_elements[2]));
	free_list_str(vec_elements);
	diameter = atof(elements[2]);
	radius = diameter / 2;
	obj->scal = vector(radius, radius, radius);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("Cone/Cylinder Color out of range\n");
	set_up_material_proprieties(elements[4], elements[5], obj);
	return (obj);
}

t_list	*readfile(char *filename)
{
	t_scene_object	*node_content;
	char			*line;
	t_list			*list;
	int				fd;
	char			*ptr;

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
		if (line[0] == '\n')
		{
			free(line);
			continue ;
		}
		ptr = ft_strtrim(line, " \n");
		node_content = handle_line(ptr, list);
		if (!node_content)
			err("Elemet no Recognized \n");
		(push_back(&list, ft_lstnew(node_content)), free(line), free(ptr));
	}
	if (!first_of(list, "C") || !first_of(list, "A") || !first_of(list, "L"))
		err("must be at least on Light Source & Camera & Ambient Light \n");
	return (list);
}
