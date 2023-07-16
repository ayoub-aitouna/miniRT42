/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:30 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMAGE_H
# define IMAGE_H
# include "types.h"

typedef struct image
{
	double	**red;
	double	**green;
	double	**blue;
}			t_image;

t_image		*initialize(void);
void		set_pixel(t_image *image, int x, int y, t_vector *color);
void		my_mlx_pixel_put(t_data *data, int x, int y, int color);
double		max_color_value(t_image *image);
void		display(void *mlx, void *win, t_image *image);
int			convert(double red, double green, double blue, double max);
#endif