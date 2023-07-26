/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 14:26:46 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/04 18:50:39 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	unsigned char		*b;

	i = 0;
	b = (unsigned char *)s;
	while (i < n)
	{
		if (b[i] == (unsigned char )c)
			return ((void *)b + i);
		i++;
	}
	return (NULL);
}
