/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 00:55:13 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/03 17:02:29 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*b;
	int		i;

	i = 0;
	b = malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (!b)
		return (0);
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	b[i] = '\0';
	return (b);
}
