/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 15:34:36 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/03 16:36:14 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*b;

	b = (char *)s;
	i = ft_strlen(s);
	while (i >= 0)
	{
		if (b[i] == (char)c)
			return ((char *) &b[i]);
		i--;
	}
	return (0);
}
