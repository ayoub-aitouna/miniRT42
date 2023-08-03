/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 04:32:25 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/parsing/headers/bonousparsing.h"
#include "headers/image.h"
#include "headers/main.h"
#include "headers/scene.h"
#include "headers/types.h"
#include "parsing/headers/parsing.h"
#define ESC 53

int	m_exit(t_mt *m_mt)
{
	mlx_destroy_window(m_mt->mlx, m_mt->mlx_win);
	printf("ESC Clicked \n");
	exit(0);
}

int	key_hook(int keycode, t_mt *mt)
{
	if (keycode == ESC)
		m_exit(mt);
	return (0);
}
