/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:59:43 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/29 20:42:29 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "headers/parsing.h"

t_scene_object	*handle_ambient(char **elements)
{
	t_scene_object	*obj;

	obj = malloc(sizeof(t_scene_object));
	if (double_ptr_size(elements) != 3)
	{
		printf("%d\n", double_ptr_size(elements));
		err("1error in args\n");
	}
	obj->type = elements[0];
	obj->intensity = atof(elements[1]);
	if (!f_in_range(obj->intensity, 1, 0))
		exit(1);
	obj->color = vec_range_check(ft_split(elements[2], ','), 255, 0);
	if (!obj->color)
		exit(1);
	return (obj);
}

t_scene_object	*handle_camera(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elmnts;

	obj = malloc(sizeof(t_scene_object));
	if (!obj)
		return (NULL);
	if (double_ptr_size(elements) != 4)
		err("error in args\n");
	obj->type = elements[0];
	vec_elmnts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elmnts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elmnts[0]), atof(vec_elmnts[1]),
			atof(vec_elmnts[2]));
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("out of range\n");
	obj->field_of_view = atof(elements[3]);
	if (!f_in_range(obj->field_of_view, 180, 0))
		err("out of range\n");
	return (obj);
}

t_scene_object	*handle_light(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elemts;

	obj = malloc(sizeof(t_scene_object));
	if (!obj)
		return (NULL);
	if (double_ptr_size(elements) != 4)
		err("error in args\n");
	obj->type = elements[0];
	vec_elemts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elemts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elemts[0]), atof(vec_elemts[1]),
			atof(vec_elemts[2]));
	obj->intensity = atof(elements[2]);
	if (!f_in_range(obj->intensity, 1, 0))
		exit(1);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		exit(1);
	return (obj);
}

t_scene_object	*handle_plane(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elemts;

	obj = malloc(sizeof(t_scene_object));
	if (!obj)
		err("Error\n");
	if (double_ptr_size(elements) != 4)
	{
		write(2, "error in args\n", 14);
		exit(1);
	}
	obj->type = elements[0];
	vec_elemts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elemts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elemts[0]), atof(vec_elemts[1]),
			atof(vec_elemts[2]));
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("out of range\n");
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	return (obj);
}

t_scene_object	*handle_cy_cone(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elements;

	obj = malloc(sizeof(t_scene_object));
	if (!obj)
		err("Error\n");
	if (double_ptr_size(elements) != 6)
	{
		write(2, "2error in args\n", 14);
		exit(1);
	}
	obj->type = elements[0];
	vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elements) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elements[0]), atof(vec_elements[1]),
			atof(vec_elements[2]));
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("out of range\n");
	obj->color = vec_range_check(ft_split(elements[5], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	return (obj);
}

t_scene_object	*handle_sphere(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elements;
	double			diameter;
	double			radius;

	obj = malloc(sizeof(t_scene_object));
	if (!obj)
		err("Error\n");
	if (double_ptr_size(elements) != 4)
		err("2 error in args\n");
	obj->type = elements[0];
	vec_elements = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elements) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elements[0]), atof(vec_elements[1]),
			atof(vec_elements[2]));
	diameter = atof(elements[2]);
	radius = diameter / 2;
	obj->scal = vector(radius, radius, radius);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		err("out of range\n");
	return (obj);
}
