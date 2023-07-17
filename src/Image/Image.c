/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:45 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/17 19:56:14 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/image.h"

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

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
