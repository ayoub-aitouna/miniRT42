/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:57:57 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/26 10:48:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

int	double_ptr_size(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	err(char *msg)
{
	write(2, msg, ft_strlen(msg));
	exit(1);
}

t_vector	*vec_range_check(char **list, double max, double min)
{
	int		i;
	double	nums[3];

	i = 0;
	if (double_ptr_size(list) != 3)
		err("Vector Format incorrect !\n");
	while (list[i])
	{
		nums[i] = atof(list[i]);
		if (nums[i] < min || nums[i] > max)
			return (NULL);
		i++;
	}
	free(list);
	return (vector(nums[0], nums[1], nums[2]));
}

int	f_in_range(double value, double max, double min)
{
	if (value < min || value > max)
	{
		printf("out of range %f\n", value);
		exit(0);
	}
	return (TRUE);
}

t_list	*ReadFile(char *fileName)
{
	t_scene_object	*node_content;
	char			*line;
	t_list			*list;
	int				fd;

	list = NULL;
	fd = open(fileName, O_RDONLY);
	if (fd == -1)
	{
		write(2, "failed to open file\n", 21);
		exit(1);
	}
	while (TRUE)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		node_content = handle_line(line);
		if (!node_content)
			err("Elemet no recognized \n");
		push_back(&list, ft_lstnew(node_content));
	}
	return (list);
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
	}
	printf("\t----------------------------\n\n");
}

int	main(int ac, char **av)
{
	t_list	*scene;

	(void)ac;
	(void)av;
	scene = ReadFile("scenes/s1.rt");
	while (scene)
	{
		print_scene_object(scene->content);
		scene = scene->next;
	}
}
