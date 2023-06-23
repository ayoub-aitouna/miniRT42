#include "headers/image.h"
#include "headers/main.h"
#include "headers/types.h"

int	m_exit(void)
{
	printf("Stoped Runnig \n");
	exit(0);
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_image	*image;
	scene_t	*scene;

	image = NULL;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "RayTracing");
	scene = Scene();
	image = Render(scene);
	display(mlx, mlx_win, image);
	mlx_hook(mlx_win, 17, 0l, m_exit, NULL);
	mlx_loop(mlx);
}
