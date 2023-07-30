/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:42:52 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/30 14:25:43 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

void	free_list_str(char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		free(list[i++]);
	}
	free(list);
}

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
		printf("\treflection_pr    : ");
		print_vector(*obj->reflection_pr);
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
		printf("\treflection_pr    : ");
		print_vector(*obj->reflection_pr);
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
		printf("\treflection_pr    : ");
		print_vector(*obj->reflection_pr);
		printf("\tTexture Type    : %d\n", obj->texture_type);
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
	if (ft_strncmp(splited[0], "sp", ft_strlen(splited[0])) == 0)
		object = handle_sphere(splited);
	if (ft_strncmp(splited[0], "pl", ft_strlen(splited[0])) == 0)
		object = handle_plane(splited);
	free_list_str(splited);
	return (object);
}
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

int	main(int ac, char **av)
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
}
