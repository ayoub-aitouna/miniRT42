/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:12:29 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/03 16:29:00 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	chama(const char *set, int c)
{
	int	k;

	k = 0;
	while (set[k])
	{
		if (set[k] == c)
			return (1);
		k++;
	}
	return (0);
}

char	*ft_strtrim(char const *s, char const *set)
{
	int		i;
	int		j;
	char	*str;

	if (!s || !set)
		return (NULL);
	i = 0;
	j = ft_strlen(s) - 1;
	while (s[i] && chama(set, s[i]) == 1)
		i++;
	while (j > i && chama(set, s[j]) == 1)
		j--;
	str = ft_substr(s, i, j - i + 1);
	return (str);
}
