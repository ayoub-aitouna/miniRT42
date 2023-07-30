/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:59:43 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/30 14:25:06 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

t_scene_object	*init_t_scene_object(void)
{
	t_scene_object	*obj;

	obj = malloc(sizeof(t_scene_object));
	obj->type = NULL;
	obj->position = NULL;
	obj->color = NULL;
	obj->normal = NULL;
	obj->reflection_pr = NULL;
	obj->scal = NULL;
	obj->Texture_path = NULL;
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
								atof(mt_coefficient[1]),
								atof(mt_coefficient[2]));
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
		obj->Texture_path = ft_strdup(texture);
	}
	free_list_str(mt_coefficient);
}

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
