#include "headers/image.h"
#include "headers/main.h"
#include "headers/types.h"

void bg(void *mlx, void *win, t_image *image)
{
	int i;
	int j;

	i = 0, j = 0;
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

int m_exit(void)
{
	printf("Stoped Runnig \n");
	exit(0);
}

// int main(int ac, char **av)
// {
// 	void *mlx;
// 	void *mlx_win;
// 	t_data img;
// 	t_image *image;

// 	mlx = mlx_init();
// 	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "RayTracing");
// 	image = initialize(mlx);
// 	bg(mlx, mlx_win, image);
// 	mlx_hook(mlx_win, 17, 0l, m_exit, NULL);
// 	mlx_loop(mlx);
// }
