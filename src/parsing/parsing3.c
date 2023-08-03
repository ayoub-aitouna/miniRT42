/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/29 20:42:52 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 21:18:04 by clyamani         ###   ########.fr       */
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

int	str_equal(char *s1, char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1)) == 0);
}

int	equal_atleast_once(char *s1, char **list)
{
	int	i;

	i = 0;
	while (list[i])
	{
		if (str_equal(s1, list[i]))
			return (TRUE);
		i++;
	}
	return (FALSE);
}

t_scene_object	*handle_line(char *line, t_list *list)
{
	char			**splited;
	t_scene_object	*object;

	object = NULL;
	splited = ft_split(line, ' ');
	if (equal_atleast_once(splited[0], (char *[]){"A", "C", "L", NULL})
		&& (first_of(list, splited[0]) != NULL))
		err("Element Duplicated \n");
	if (ft_strncmp(splited[0], "A", ft_strlen(splited[0])) == 0)
		object = handle_ambient(splited);
	if (ft_strncmp(splited[0], "C", ft_strlen(splited[0])) == 0)
		object = handle_camera(splited);
	if (ft_strncmp(splited[0], "L", ft_strlen(splited[0])) == 0)
		object = handle_light(splited);
	if (ft_strncmp(splited[0], "cy", ft_strlen(splited[0])) == 0)
		object = handle_cy_cone(splited);
	if (ft_strncmp(splited[0], "sp", ft_strlen(splited[0])) == 0)
		object = handle_sphere(splited);
	if (ft_strncmp(splited[0], "pl", ft_strlen(splited[0])) == 0)
		object = handle_plane(splited);
	free_list_str(splited);
	return (object);
}
