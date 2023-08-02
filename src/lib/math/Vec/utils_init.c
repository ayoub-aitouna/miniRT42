/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 10:58:58 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/02 10:59:55 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

void	free_at_index(void *ptr1, void *ptr2, int index)
{
	if (index == 0 || index == 2)
		free(ptr1);
	if (index == 1 || index == 2)
		free(ptr2);
}
