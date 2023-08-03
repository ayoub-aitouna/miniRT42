/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:02:43 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bonus/parsing/headers/bonousparsing.h"
#include "headers/image.h"
#include "headers/main.h"
#include "headers/scene.h"
#include "headers/types.h"
#include "parsing/headers/parsing.h"

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

int	main(int ac, char **av)
{
	t_mt	m_mt;
	t_list	*l_scene;

	if (ac != 2)
		err("invalide args !!\n");
	l_scene = parse_scene(av[1]);
	m_mt = (t_mt){.scene = NULL, .image = NULL};
	m_mt.image = NULL;
	m_mt.mlx = mlx_init();
	m_mt.mlx_win = mlx_new_window(m_mt.mlx, WIDTH, HEIGHT, "miniRT");
	m_mt.scene = scene(m_mt.mlx, m_mt.mlx_win, l_scene);
	m_mt.image = render(m_mt.scene, m_mt.mlx, m_mt.mlx_win);
	display(m_mt.mlx, m_mt.mlx_win, m_mt.image);
	deletescene(m_mt.scene);
	system("leaks miniRT");
	mlx_key_hook(m_mt.mlx_win, key_hook, &m_mt);
	mlx_hook(m_mt.mlx_win, 17, 0l, m_exit, &m_mt);
	mlx_loop(m_mt.mlx);
	return (0);
}
