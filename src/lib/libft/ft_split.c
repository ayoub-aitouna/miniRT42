/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 12:56:56 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/04 21:56:26 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count(char c, const char *s)
{
	int	i;
	int	m;

	m = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			m++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (m);
}

static char	**ft_free(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (0);
}

static char	*allocation(const char *s, int n)
{
	char	*a;
	int		i;

	a = malloc(sizeof(char) * n + 1);
	if (!a)
		return (NULL);
	i = 0;
	while (s[i] && i < n)
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**a;

	i = 0;
	k = 0;
	a = ft_calloc(count(c, s) + 1, sizeof(char *));
	if (!a)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		j = i;
		while (s[i] && s[i] != c)
			i++;
		if (i > j)
		{
			a[k] = allocation(s + j, i - j);
			if (!a[k++])
				return (ft_free(a));
		}
	}
	return (a);
}
