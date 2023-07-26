/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:35:49 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/02 16:55:58 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	count(int nb)
{
	int		count;
	long	n;

	n = (long) nb;
	count = 0;
	if (n == 0)
	{
		count ++;
	}
	if (n < 0)
	{
		n *= -1;
		count ++;
	}
	while (n > 0)
	{
		n /= 10;
		count ++;
	}
	return (count);
}

static	char	*fill_str(char *str, long nbr, int count)
{
	int		b;

	b = 0;
	str[count] = '\0';
	if (nbr < 0)
	{
		str[0] = '-';
		nbr *= -1;
		b = 1;
	}
	while (--count >= b)
	{
		str[count] = (nbr % 10) + 48;
		nbr = nbr / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*str;
	long	nbr;

	nbr = (long) n;
	len = count(n);
	str = malloc(sizeof(char) * (len +1));
	if (!str)
		return (0);
	str = fill_str(str, nbr, len);
	return (str);
}
