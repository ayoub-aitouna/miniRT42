/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:32:32 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/23 15:47:12 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
# 
char	*lire_accorder(char *ligne, int fd)
{
	char	*buff;
	int		return_lire;

	buff = malloc(sizeof(char) *(BUFFER_SIZE + 1));
	if (!buff)
		return (NULL);
	return_lire = 1;
	while (!ft_strchr (ligne, '\n') && return_lire != 0)
	{
		return_lire = read(fd, buff, BUFFER_SIZE);
		if (return_lire == -1)
		{
			free (buff);
			free (ligne);
			return (NULL);
		}
		buff[return_lire] = '\0';
		ligne = ft__strjoin(ligne, buff);
	}
	free (buff);
	return (ligne);
}

char	*check_stc(char *stc_str)
{
	int		i;
	char	*str;

	i = 0;
	if (!stc_str[i])
		return (NULL);
	while (stc_str[i] && stc_str[i] != '\n')
		i++;
	str = malloc(sizeof(char) * (i + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (stc_str[i] != '\n' && stc_str[i])
	{
		str[i] = stc_str[i];
		i++;
	}
	if (stc_str[i] == '\n')
	{
		str[i] = stc_str[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*mis_ajour(char *stc_str)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (stc_str[i] != '\n' && stc_str[i])
		i++;
	if (!stc_str[i])
	{
		free(stc_str);
		return (NULL);
	}
	str = malloc(sizeof(char) * (ft_strlen(stc_str) - i));
	if (!str)
		return (NULL);
	i++;
	j = 0;
	while (stc_str[i])
		str[j++] = stc_str[i++];
	str[j] = '\0';
	free (stc_str);
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*stc_str;
	char		*resultat;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stc_str = lire_accorder(stc_str, fd);
	if (!stc_str)
		return (NULL);
	resultat = check_stc(stc_str);
	stc_str = mis_ajour(stc_str);
	return (resultat);
}
