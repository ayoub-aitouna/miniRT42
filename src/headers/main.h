/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:33 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:04:17 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../headers/image.h"
# include "../headers/scene.h"
# include "../headers/types.h"
# include "../lib/math/headers/gtfm.h"
# include "../lib/math/headers/matrix.h"
# include "image.h"
# include <fcntl.h>
# include <limits.h>
# include <mlx.h>
# include <stdarg.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# define WIDTH 1280
# define HEIGHT 720
# define ESC 53
# ifndef BONUS_ENABLES
#  define BONUS_ENABLES 0
# endif

typedef struct mt
{
	t_image	*image;
	t_scene	*scene;
	void	*mlx;
	void	*mlx_win;
}			t_mt;

int			m_exit(t_mt *m_mt);
int			key_hook(int keycode, t_mt *mt);
t_list		*parse_scene(char *file_name);
#endif