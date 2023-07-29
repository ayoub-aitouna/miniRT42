/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 15:32:10 by clyamani          #+#    #+#             */
/*   Updated: 2023/07/23 15:47:49 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 7

# endif

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include "../lib/lib.h"

ssize_t	read(int fd, void *buf, size_t nbyte);
char	*get_next_line(int fd);
char	*mis_ajour(char *stc_str);
char	*check_stc(char *stc_str);
char	*lire_accorder(char *ligne, int fd);
char	*ft__strjoin(char *s1, char *s2);
#endif