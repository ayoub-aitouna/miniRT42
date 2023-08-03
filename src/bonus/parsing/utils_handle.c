/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/03 22:03:35 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/03 22:03:52 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/bonousparsing.h"

t_list	*bns_readfile(char *filename)
{
	int				fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		err("failed to open file\n");
	return (get_bns_file_content(fd));
}
