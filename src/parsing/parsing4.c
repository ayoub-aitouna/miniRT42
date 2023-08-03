/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:27:52 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 04:32:40 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

void	delete_object_scene(t_scene_object *obj)
{
	if (obj == NULL)
		return ;
	if (obj->type != NULL)
		free(obj->type);
	if (obj->position != NULL)
		free(obj->position);
	if (obj->color != NULL)
		free(obj->color);
	if (obj->normal != NULL)
		free(obj->normal);
	if (obj->reflection != NULL)
		free(obj->reflection);
	if (obj->refraction != NULL)
		free(obj->refraction);
	if (obj->scal != NULL)
		free(obj->scal);
	if (obj->texture_path != NULL)
		free(obj->texture_path);
	free(obj);
}

t_scene_object	*handle_light(char **elements)
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

void	strip_nl(char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (src[i] == '\n')
			src[i] = 0;
		i++;
	}
}

void	exit_f_out_of_range(t_vector2 *vec, double max1, double max2)
{
	f_in_range(vec->x, max1, 0);
	f_in_range(vec->y, max2, 0);
}
