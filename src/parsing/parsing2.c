/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:59:43 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/02 10:48:09 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

t_scene_object	*first_of(t_list *l_scene, char *type)
{
	while (l_scene)
	{
		if (!strncmp(((t_scene_object *)l_scene->content)->type, type,
				ft_strlen(type)))
			return (l_scene->content);
		l_scene = l_scene->next;
	}
	return (NULL);
}

t_vector	*convert_vec_color(t_vector *color)
{
	color->x /= 255;
	color->y /= 255;
	color->z /= 255;
	return (color);
}

t_scene_object	*init_t_scene_object(void)
{
	t_scene_object	*obj;

	obj = malloc(sizeof(t_scene_object));
	obj->type = NULL;
	obj->position = NULL;
	obj->color = NULL;
	obj->normal = NULL;
	obj->reflection = NULL;
	obj->refraction = NULL;
	obj->scal = NULL;
	obj->texture_path = NULL;
	return (obj);
}

t_scene_object	*handle_ambient(char **elements)
{
	t_scene_object	*obj;

	obj = init_t_scene_object();
	if (double_ptr_size(elements) != 3)
	{
		printf("%d\n", double_ptr_size(elements));
		err("1error in args\n");
	}
	obj->type = ft_strdup(elements[0]);
	obj->intensity = atof(elements[1]);
	f_in_range(obj->intensity, 1, 0);
	obj->color = vec_range_check(ft_split(elements[2], ','), 255, 0);
	if (!obj->color)
		err("A color out of range. \n");
	return (obj);
}

t_scene_object	*handle_camera(char **elements)
{
	t_scene_object	*obj;
	char			**vec_elmnts;

	obj = init_t_scene_object();
	if (!obj)
		return (NULL);
	if (double_ptr_size(elements) != 4)
		err("error in args\n");
	obj->type = ft_strdup(elements[0]);
	vec_elmnts = ft_split(elements[1], ',');
	if (double_ptr_size(vec_elmnts) != 3)
		err("error in args\n");
	obj->position = vector(atof(vec_elmnts[0]), atof(vec_elmnts[1]),
			atof(vec_elmnts[2]));
	free_list_str(vec_elmnts);
	obj->normal = vec_range_check(ft_split(elements[2], ','), 1, -1);
	if (!obj->normal)
		err("Camer Normal out of range\n");
	obj->field_of_view = atof(elements[3]);
	f_in_range(obj->field_of_view, 180, 0);
	return (obj);
}
