/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:48 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 23:17:03 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/image.h"
#include "headers/main.h"
#include "headers/scene.h"
#include "headers/types.h"

#define ESC 53

typedef struct mt
{
	t_image	*image;
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;
}			t_mt;

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

int	main(void)
{
	t_mt	m_mt;

	m_mt = (t_mt){.scene = NULL, .image = NULL};
	m_mt.image = NULL;
	m_mt.mlx = mlx_init();
	m_mt.mlx_win = mlx_new_window(m_mt.mlx, WIDTH, HEIGHT, "miniRT");
	m_mt.scene = scene(m_mt.mlx, m_mt.mlx_win);
	m_mt.image = render(m_mt.scene, m_mt.mlx, m_mt.mlx_win);
	display(m_mt.mlx, m_mt.mlx_win, m_mt.image);
	deletescene(m_mt.scene);
	mlx_key_hook(m_mt.mlx_win, key_hook, &m_mt);
	mlx_hook(m_mt.mlx_win, 17, 0l, m_exit, &m_mt);
	sleep(1);
	system("leaks miniRT");
	mlx_loop(m_mt.mlx);
}
