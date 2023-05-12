#include "headers/main.h"
#include "headers/types.h"
#include "headers/image.h"

double **init_channel()
{
    double **channel = malloc(sizeof(double *) * HEIGHT);
    int i = 0;
    while (i < HEIGHT)
        channel[i++] = malloc(sizeof(double) * WIDTH);
    return (channel);
}

t_image *initialize(void *mlx)
{
    t_image *image = malloc(sizeof(t_image));

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

void display(void *mlx, void *win, t_image *image)
{
    int i = 0, j = 0;
    t_data img;
    double max = calculat_max(image->red);
    double max_g = calculat_max(image->green);
    if (max_g > max)
        max = max_g;
    double max_b = calculat_max(image->blue);
    if (max_b > max)
        max = max_b;
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

double calculat_max(double **channel)
{
    int i = 0, j = 0;
    double max = 0.0;
    while (i < HEIGHT)
    {
        j = 0;
        while (j < WIDTH)
        {
            if (channel[i][j] > max)
                max = channel[i][j];
            j++;
        }
        i++;
    }
    return (max);
}

int convert(double red, double green, double blue, double max, int endian)
{
    unsigned char r = (red / max) * 255;
    unsigned char g = (green / max) * 255;
    unsigned char b = (blue / max) * 255;
    int value = (r << 16) + (g << 8) + b;
    return (value);
}

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char *dst;
    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}