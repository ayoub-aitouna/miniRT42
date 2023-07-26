/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:39:29 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/04 22:24:17 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	slen;
	size_t	dtlen;

	dtlen = ft_strlen(dst);
	slen = ft_strlen(src);
	i = 0;
	if (dstsize == 0)
		return (slen);
	if (dtlen >= dstsize)
		return (slen + dstsize);
	while (src[i] != '\0' && i < dstsize - dtlen - 1)
	{
		dst[i + dtlen] = src[i];
		i++;
	}
	dst[i + dtlen] = '\0';
	return (slen + dtlen);
}
