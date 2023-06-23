#ifndef RTCIMAGE_H
#define RTCIMAGE_H
#include "types.h"

typedef struct image
{
    double **red;
    double **green;
    double **blue;
} t_image;

t_image *initialize(void);
void set_pixel(t_image *image, int x, int y, double r, double g, double b);
void my_mlx_pixel_put(t_data *data, int x, int y, int color);
double max_color_value(t_image *image);
void display(void *mlx, void *win, t_image *image);
int convert(double red, double green, double blue, double max);
#endif