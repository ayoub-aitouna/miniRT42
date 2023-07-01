#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_data;

int	main(void)
{
	void *mlx_ptr = mlx_init();
	void *mlx_win = mlx_new_window(mlx_ptr, 150, 150, "sdf");
	int a;

	t_data *img = NULL;
	img = malloc(sizeof(t_data));
	img->img = mlx_xpm_file_to_image(mlx_ptr, "./assets/dragon.xpm", &a, &a);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel,
			&img->line_length, &img->endian);
	unsigned int all = (*(unsigned int *)img->addr);
	double r = (all >> 16 & 255) / 255.f;
	double g = ((all >> 8) & 255) / 255.f;
	double b = (all & 255) / 255.f;
	printf("{%f, %f, %f} all : %x\n", r, g, b, all);
	mlx_loop(mlx_ptr);
}