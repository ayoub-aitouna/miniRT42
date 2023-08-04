/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 21:57:57 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/04 21:56:03 by aaitouna         ###   ########.fr       */
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
	char	*err;

	err = "Error\n";
	write(2, err, ft_strlen(err));
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
	free_list_str(list);
	return (vector(nums[0], nums[1], nums[2]));
}

int	f_in_range(double value, double max, double min)
{
	if (value < min || value > max)
	{
		printf("value : %f , range [%f, %f]", value, min, max);
		err("out of range \n");
	}
	return (TRUE);
}

/**
 * checks it files ends with
 * example : <.rt>
 * example : ./scenes/example.rt
 */
int	check_extention(char *file_name, char *extention)
{
	size_t	pos;
	size_t	npos;
	size_t	i;

	if (ft_strlen(file_name) <= ft_strlen(extention) || !file_name || !extention
		|| !ft_strlen(file_name) || !ft_strlen(extention))
		return (FALSE);
	pos = ft_strlen(file_name) - ft_strlen(extention);
	npos = (pos - 1);
	while (npos > 0 && file_name[npos] != '/')
		npos--;
	if (npos == (pos - 1))
		return (FALSE);
	i = 0;
	while (file_name[pos])
	{
		if (file_name[pos] != extention[i])
			return (FALSE);
		i++;
		pos++;
	}
	if (i < (ft_strlen(extention) - 1))
		return (FALSE);
	return (TRUE);
}
