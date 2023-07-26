/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:53:25 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/04 18:52:16 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*a;
	unsigned char	*b;
	size_t			i;

	i = 0;
	a = (unsigned char *) dst;
	b = (unsigned char *) src;
	if (!a && !b)
		return (NULL);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		a[i] = b[i];
		i++;
	}
	return (dst);
}
