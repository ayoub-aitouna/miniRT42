/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 20:45:20 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/04 22:06:34 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	int				i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (dst > src)
	{
		i = len - 1;
		while (i >= 0)
		{
			a[i] = b[i];
			i--;
		}
	}
	else if (dst < src)
	{
		ft_memcpy(dst, src, len);
	}
	return (dst);
}
