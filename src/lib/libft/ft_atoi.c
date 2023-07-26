/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/09 17:41:56 by clyamani          #+#    #+#             */
/*   Updated: 2022/11/02 22:51:13 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int						i;
	int						signe;
	unsigned long long		nmbr;

	i = 0;
	signe = 1;
	nmbr = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = signe * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		nmbr = nmbr * 10 + (str[i] - 48);
		i++;
	}
	if (nmbr >= 9223372036854775807 && signe > 0)
		return (-1);
	else if (nmbr > 9223372036854775807 && signe < 0)
		return (0);
	return (nmbr * signe);
}
