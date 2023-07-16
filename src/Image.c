/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/image.h"
#include "headers/main.h"
#include "headers/types.h"

double	**init_channel(void)
{
	double	**channel;
	int		i;

	channel = malloc(sizeof(double *) * HEIGHT);
	i = 0;
	while (i < HEIGHT)
		channel[i++] = malloc(sizeof(double) * WIDTH);
	return (channel);
}

t_image	*initialize(void)
{
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->red = init_channel();
	image->green = init_channel();
	image->blue = init_channel();
	return (image);
}

void	set_pixel(t_image *image, int x, int y, t_vector *color)
{
	image->red[y][x] = color->x;
	image->green[y][x] = color->y;
	image->blue[y][x] = color->z;
}

void	display(void *mlx, void *win, t_image *image)
{
	int		i;
	t_data	img;
	double	max;
	int		j;

	i = 0;
	if (!image)
		return ;
	max = max_color_value(image);
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
			&img.endian);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(&img, j, i, convert(image->red[i][j],
					image->green[i][j], image->blue[i][j], max));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
	mlx_destroy_image(mlx, img.img);
}

int	convert(double red, double green, double blue, double max)
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
	int				value;

	r = (red / max) * 255;
	g = (green / max) * 255;
	b = (blue / max) * 255;
	value = (r << 16) + (g << 8) + b;
	return (value);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

double	max_in_channel(double **channel)
{
	int		x;
	int		y;
	double	max;
	double	value;

	value = 0;
	max = 0;
	x = 0;
	y = 0;
	while (x < WIDTH)
	{
		y = 0;
		while (y < HEIGHT)
		{
			value = channel[y][x];
			if (value > max)
				max = value;
			y++;
		}
		x++;
	}
	return (max);
}

double	max_color_value(t_image *image)
{
	double	m_overall_max;
	double	value;

	m_overall_max = max_in_channel(image->red);
	value = max_in_channel(image->green);
	if (value > m_overall_max)
		m_overall_max = value;
	value = max_in_channel(image->blue);
	if (value > m_overall_max)
		m_overall_max = value;
	return (m_overall_max);
}
