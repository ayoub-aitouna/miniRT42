/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:36:35 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/03 14:59:10 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*a;

	i = 0;
	if (start >= ft_strlen(s))
	{
		a = malloc(sizeof(char));
		if (!a)
			return (0);
		a[0] = '\0';
		return (a);
	}
	if (len > ft_strlen(s))
		a = malloc(sizeof(char) * (ft_strlen(s) - start + 1));
	else
		a = malloc (sizeof(char) * len + 1);
	if (!a)
		return (0);
	while (s[start + i] && i < len)
	{
		a[i] = s[start + i];
		i++;
	}
	a[i] = '\0';
	return (a);
}
