/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 11:14:30 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/26 10:47:56 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib/lib.h"
#include <math.h>

double	fraction_index(int value)
{
	long	i;

	i = 0;
	while (value > 10)
	{
		value /= 10;
		i++;
	}
	return (pow(10, i + 1));
}

char	*ft_str_append(char *s, char c)
{
	int		i;
	int		len;
	char	*new_str;

	i = 0;
	len = ft_strlen(s);
	new_str = malloc((len + 3) * sizeof(char));
	if (!new_str)
		exit(0);
	while (i < len)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i++] = c;
	new_str[i] = 0;
	if (s != NULL)
		free(s);
	return (new_str);
}

char	**dot_split(const char *s)
{
	int		i;
	int		j;
	char	**result;

	result = malloc(sizeof(char *) * 2);
	result[0] = NULL;
	result[1] = NULL;
	j = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == '.')
			break ;
		result[0] = ft_str_append(result[0], s[i]);
		i++;
	}
	while (s[i] && j < 6)
	{
		result[1] = ft_str_append(result[1], s[i]);
		i++;
	}
	return (result);
}

double	ft_atof(const char *str)
{
	int		part_1;
	int		part_2;
	double	fractional_part;
	char	**seperated;

	part_1 = 0;
	fractional_part = 0;
	if (!str || ft_strlen(str) == 0)
		return (0);
	seperated = dot_split(str);
	if (!seperated)
		return (0);
	if (seperated[0])
		part_1 = ft_atoi(seperated[0]);
	if (seperated[1])
	{
		if (ft_strlen(seperated[1]) > 6)
			seperated[1][6] = 0;
		part_2 = ft_atoi(seperated[1]);
		fractional_part = (double)part_2 / fraction_index(part_2);
	}
	return ((double)part_1 + fractional_part);
}
