/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 00:29:20 by aaitouna          #+#    #+#             */
/*   Updated: 2022/11/02 00:29:22 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	gt_strlen(const char *c)
{
	int	i;

	if (c == NULL)
		return (0);
	i = 0;
	while (c[i])
		i++;
	return (i);
}

char	*gt_strchr(const char *s, int c)
{
	int				i;
	unsigned char	uc;

	if (!s)
		return (0);
	uc = (unsigned char)c;
	i = 0;
	while (s[i] && s[i] != uc)
	{
		i++;
	}
	if (s[i] == uc)
		return ((char *)&s[i]);
	return (0);
}

void	cpy(char *holder, char *cursor, char *n_holder)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (holder[j])
		n_holder[i++] = holder[j++];
	j = 0;
	while (cursor[j])
		n_holder[i++] = cursor[j++];
	n_holder[i] = '\0';
}

char	*gt_strjoin(char *holder, char *cursor)
{
	size_t	len1;
	size_t	len2;
	char	*n_holder;

	if (!cursor || cursor[0] == 0)
		return (NULL);
	if (!holder)
	{
		holder = (char *)malloc(1 * sizeof(char));
		holder[0] = '\0';
	}
	len2 = gt_strlen(cursor);
	len1 = gt_strlen(holder);
	n_holder = malloc(len1 + len2 + 1);
	if (n_holder == NULL)
		return (NULL);
	cpy(holder, cursor, n_holder);
	free(holder);
	return (n_holder);
}
