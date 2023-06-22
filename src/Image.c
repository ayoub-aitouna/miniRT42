#include "headers/image.h"
#include "headers/main.h"
#include "headers/types.h"

double **init_channel(void)
{
	double **channel;
	int i;

	channel = malloc(sizeof(double *) * HEIGHT);
	i = 0;
	while (i < HEIGHT)
		channel[i++] = malloc(sizeof(double) * WIDTH);
	return (channel);
}

t_image *initialize(void *mlx)
{
	t_image *image;

	image = malloc(sizeof(t_image));
	image->red = init_channel();
	image->green = init_channel();
	image->blue = init_channel();
	return (image);
}

void set_pixel(t_image *image, int x, int y, double r, double g, double b)
{
	image->red[y][x] = r;
	image->green[y][x] = g;
	image->blue[y][x] = b;
}
double MAX(t_image *image);
void display(void *mlx, void *win, t_image *image)
{
	int i;
	t_data img;
	double max;
	double max_g;
	double max_b;
	int j;

	i = 0;
	j = 0;
	if (!image)
		return;
	max = MAX(image);
	img.img = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			my_mlx_pixel_put(&img, j, i, convert(image->red[i][j], image->green[i][j], image->blue[i][j], max, img.endian));
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, win, img.img, 0, 0);
}

// double calculat_max(double **channel)
// {
// 	int i;
// 	double max;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	max = 0.0;
// 	while (i < HEIGHT)
// 	{
// 		j = 0;
// 		while (j < WIDTH)
// 		{
// 			if (channel[i][j] > max)
// 				max = channel[i][j];
// 			j++;
// 		}
// 		i++;
// 	}
// 	return (max);
// }

double MAX(t_image *image)
{
	double m_max_red = 0.0;
	double m_max_green = 0.0;
	double m_max_blue = 0.0;
	double m_overall_max = 0.0;
	for (int x = 0; x < WIDTH; x++)
	{

		for (int y = 0; y < HEIGHT; y++)
		{
			double redValue = image->red[y][x];
			double greenValue = image->green[y][x];
			double blueValue = image->blue[y][x];

			if (redValue > m_max_red)
				m_max_red = redValue;
			if (blueValue > m_max_blue)
				m_max_blue = blueValue;
			if (greenValue > m_max_green)
				m_max_green = greenValue;

			if (m_max_red > m_overall_max)
				m_overall_max = m_max_red;
			if (m_max_green > m_overall_max)
				m_overall_max = m_max_green;
			if (m_max_blue > m_overall_max)
				m_overall_max = m_max_blue;
		}
	}
	return (m_overall_max);
}

int convert(double red, double green, double blue, double max, int endian)
{
	unsigned char r;
	unsigned char g;
	unsigned char b;
	int value;

	r = (red / max) * 255;
	g = (green / max) * 255;
	b = (blue / max) * 255;
	value = (r << 16) + (g << 8) + b;
	return (value);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char *dst;
	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}