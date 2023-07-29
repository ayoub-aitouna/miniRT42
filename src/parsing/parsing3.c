/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 15:31:30 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/29 16:55:11 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

void	print_scene_object(t_scene_object *obj)
{
	printf("\t----------------------------\n"
		"type %s :\n",
		obj->type);
	if (!strcmp(obj->type, "C"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tNormal   : ");
		print_vector(*obj->normal);
		printf("\tFOV      : %.3f\n", obj->field_of_view);
	}
	if (!strcmp(obj->type, "A"))
	{
		printf("\tIntensity: %.3f\n", obj->intensity);
		printf("\tColor    : ");
		print_vector(*obj->color);
	}
	if (!strcmp(obj->type, "L"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tIntensity: %.3f\n", obj->intensity);
		printf("\tColor    : ");
		print_vector(*obj->color);
	}
	if (!strcmp(obj->type, "pl"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tNormal   : ");
		print_vector(*obj->normal);
		printf("\tColor    : ");
		print_vector(*obj->color);
	}
	if (!strcmp(obj->type, "cy"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tNormal   : ");
		print_vector(*obj->normal);
		printf("\tColor    : ");
		print_vector(*obj->color);
	}
	if (!strcmp(obj->type, "co"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tNormal   : ");
		print_vector(*obj->normal);
		printf("\tColor    : ");
		print_vector(*obj->color);
	}
	printf("\t----------------------------\n\n");
}

t_scene_object	*handle_line(char *line)
{
	char			**splited;
	t_scene_object	*object;

	object = NULL;
	splited = ft_split(line, ' ');
	if (ft_strncmp(splited[0], "A", ft_strlen(splited[0])) == 0)
		object = handle_ambient(splited);
	if (ft_strncmp(splited[0], "C", ft_strlen(splited[0])) == 0)
		object = handle_camera(splited);
	if (ft_strncmp(splited[0], "L", ft_strlen(splited[0])) == 0)
		object = handle_light(splited);
	if (ft_strncmp(splited[0], "cy", ft_strlen(splited[0])) == 0
		|| ft_strncmp(splited[0], "co", ft_strlen(splited[0])) == 0)
		object = handle_cy_cone(splited);
	if (ft_strncmp(splited[0], "pl", ft_strlen(splited[0])) == 0)
		object = handle_plane(splited);
	return (object);
}

int	main(int ac, char **av)
{
	t_list	*scene;

	(void)ac;
	(void)av;
	scene = readfile("scenes/s1.rt");
	while (scene)
	{
		print_scene_object(scene->content);
		scene = scene->next;
	}
}
