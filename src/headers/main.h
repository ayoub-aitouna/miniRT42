/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:33 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:21:33 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT
#define RT
#include <stdlib.h>
#include <mlx.h>
#include <limits.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>
#include <fcntl.h>
#include "image.h"
#include "../lib/math/headers/matrix.h"
#include "../lib/math/headers/gtfm.h"
#define WIDTH 1280
#define HEIGHT 720
scene_t *Scene();
t_image *Render(scene_t *scene);
#endif