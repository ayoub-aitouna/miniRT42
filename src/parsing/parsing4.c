/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/31 19:27:52 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/31 19:34:06 by clyamani         ###   ########.fr       */
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
	if (obj->reflection_pr != NULL)
		free(obj->reflection_pr);
	if (obj->scal != NULL)
		free(obj->scal);
	if (obj->Texture_path != NULL)
		free(obj->Texture_path);
}

int	_diabled_main(int ac, char **av)
{
	t_list	*scene;

	(void)ac;
	(void)av;
	if (ac != 2)
		err("invalide args !!\n");
	scene = readfile(av[1]);
	while (scene)
	{
		print_scene_object(scene->content);
		delete_object_scene(scene->content);
		scene = scene->next;
	}
	return (0);
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
	if (!f_in_range(obj->intensity, 1, 0))
		exit(1);
	obj->color = vec_range_check(ft_split(elements[3], ','), 255, 0);
	if (!obj->color)
		exit(1);
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

void	set_up_material_proprieties(char **mt_coefficient, char *texture,
		t_scene_object *obj)
{
	strip_nl(texture);
	if (double_ptr_size(mt_coefficient) != 3)
		err("error in args\n");
	obj->reflection_pr = vector(atof(mt_coefficient[0]),
			atof(mt_coefficient[1]), atof(mt_coefficient[2]));
	if (!f_in_range(obj->reflection_pr->x, 1, 0))
		exit(1);
	if (!f_in_range(obj->reflection_pr->y, 1, 0))
		exit(1);
	if (!f_in_range(obj->reflection_pr->z, 100, 0))
		exit(1);
	if (!ft_strncmp(texture, "NON", ft_strlen(texture)))
		obj->texture_type = NON;
	else if (ft_strncmp(texture, "CHECKBOARD", ft_strlen(texture)) == 0)
		obj->texture_type = CHECKBOARD;
	else
	{
		obj->texture_type = BUMPMAPTEXTURE;
		if (!check_extention(texture, ".xpm"))
			err("texture extention invalide \n");
		obj->Texture_path = ft_strdup(texture);
	}
	free_list_str(mt_coefficient);
}
