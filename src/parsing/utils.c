/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 14:43:38 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 04:20:33 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/parsing.h"

void	free_linkedlst(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current);
		current = next;
	}
}

void	set_up_material_proprieties(char *mt_coefficient, char *texture,
		t_scene_object *obj)
{
	char	**elemts;
	char	**r_c;
	char	**t_c;

	elemts = ft_split(mt_coefficient, ':');
	if (double_ptr_size(elemts) != 2)
		err("mt : error in args\n");
	r_c = ft_split(elemts[0], ',');
	t_c = ft_split(elemts[1], ',');
	if (double_ptr_size(r_c) != 2 || double_ptr_size(t_c) != 2)
		err("mt rc||tc:  error in args\n");
	obj->reflection = vec2(atof(r_c[0]), atof(r_c[1]));
	exit_f_out_of_range(obj->reflection, 1, 100);
	obj->refraction = vec2(atof(t_c[0]), atof(t_c[1]));
	exit_f_out_of_range(obj->refraction, 1, 4);
	if (!ft_strncmp(texture, "NON", ft_strlen(texture)))
		obj->texture_type = NON;
	else if (ft_strncmp(texture, "CHECKBOARD", ft_strlen(texture)) == 0)
		obj->texture_type = CHECKBOARD;
	else
	{
		obj->texture_type = BUMPMAPTEXTURE;
		obj->texture_path = ft_strdup(texture);
	}
	(free_list_str(elemts), free_list_str(r_c), free_list_str(t_c));
}

void	check_for_file(char *filename)
{
	if (!check_extention(filename, ".rt"))
		err("invalide Extention !!");
}
