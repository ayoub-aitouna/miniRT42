#include "headers/main.h"
#include "headers/types.h"
#include "headers/image.h"

void bg(void *mlx, void *win, t_image *image)
{
	int i = 0, j = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			set_pixel(image, j, i, .9, .5, .2);
			j++;
		}
		i++;
	}
	display(mlx, win, image);
}

int main(int ac, char **av)
{
	void *mlx;
	void *mlx_win;
	t_data img;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Hello world!");
	t_image *image = initialize(mlx);
	bg(mlx, mlx_win, image);
	mlx_loop(mlx);
}
