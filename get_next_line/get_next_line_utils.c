/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 18:10:23 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/23 15:48:32 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


char	*ft__strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	s1len;
	size_t	s2len;
	char	*str;

	i = 0;
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	str = malloc(s1len + s2len + 1);
	if (!str)
		return (NULL);
	while (i < s1len)
	{
		str[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2len)
	{
		str[i + s1len] = s2[i];
		i++;
	}
	str[s1len + s2len] = '\0';
	free(s1);
	return (str);
}
