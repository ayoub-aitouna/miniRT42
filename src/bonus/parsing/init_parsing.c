/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:27:52 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 04:22:03 by aaitouna         ###   ########.fr       */
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

void print_scene_object_bns(t_scene_object *obj)
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
		printf("\treflection    : %f, %f, refraction %f, %f \n", obj->reflection->x,
			   obj->reflection->y, obj->refraction->x, obj->refraction->y);
		printf("\tTexture Type    : %d\n", obj->texture_type);
	}
	if (!strcmp(obj->type, "co") || !strcmp(obj->type, "cy"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tNormal   : ");
		print_vector(*obj->normal);
		printf("\tScal   : ");
		print_vector(*obj->scal);
		printf("\tColor    : ");
		print_vector(*obj->color);
		printf("\treflection    : %f, %f, refraction %f, %f \n", obj->reflection->x,
			   obj->reflection->y, obj->refraction->x, obj->refraction->y);
		printf("\tTexture Type    : %d\n", obj->texture_type);
	}
	if (!strcmp(obj->type, "sp"))
	{
		printf("\tPosition : ");
		print_vector(*obj->position);
		printf("\tScal   : ");
		print_vector(*obj->scal);
		printf("\tColor    : ");
		print_vector(*obj->color);
		printf("\treflection    : %f, %f, refraction %f, %f \n", obj->reflection->x,
			   obj->reflection->y, obj->refraction->x, obj->refraction->y);
		printf("\tTexture Type    : %d\n", obj->texture_type);
	}
	printf("\t----------------------------\n\n");
}

t_scene_object *handle_line_bonus(char *line, t_list *list)
{
	char **splited;
	t_scene_object *object;

	object = NULL;
	splited = ft_split(line, ' ');
	if (equal_atleast_once(splited[0], (char *[]){"A", "C", NULL}) && (first_of(list, splited[0]) != NULL))
		err("Element Duplicated \n");
	if (ft_strncmp(splited[0], "A", ft_strlen(splited[0])) == 0)
		object = handle_ambient(splited);
	if (ft_strncmp(splited[0], "C", ft_strlen(splited[0])) == 0)
		object = handle_camera(splited);
	if (ft_strncmp(splited[0], "L", ft_strlen(splited[0])) == 0)
		object = handle_light(splited);
	if (ft_strncmp(splited[0], "cy", ft_strlen(splited[0])) == 0 || ft_strncmp(splited[0], "co", ft_strlen(splited[0])) == 0)
		object = bns_handle_cy_cone(splited);
	if (ft_strncmp(splited[0], "sp", ft_strlen(splited[0])) == 0)
		object = bns_handle_sphere(splited);
	if (ft_strncmp(splited[0], "pl", ft_strlen(splited[0])) == 0)
		object = bns_handle_plane(splited);
	free_list_str(splited);
	return (object);
}
