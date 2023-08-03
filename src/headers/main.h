/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:33 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 04:11:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAIN_H
# define MAIN_H
# include "../lib/math/headers/gtfm.h"
# include "../lib/math/headers/matrix.h"
#include "../headers/image.h"
#include "../headers/scene.h"
#include "../headers/types.h"
#include "image.h"
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

typedef struct mt
{
    t_image *image;
    t_scene *scene;
    void *mlx;
    void *mlx_win;
} t_mt;

int		m_exit(t_mt *m_mt);
int		key_hook(int keycode, t_mt *mt);
void	print_scene(t_list *scene);
#endif