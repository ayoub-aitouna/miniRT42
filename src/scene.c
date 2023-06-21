
#include "headers/scene.h"

scene_t *Scene()
{
	scene_t *scene = malloc(sizeof(scene_t));
	scene->m_object_list = NULL;
	object_t *sphere = create_sphere(vector(0, 0, 0), vector(0, 0, 0),
			vector(1, 1, 1), vector(.9, .5, .2));
	push_back(&scene->m_object_list, ft_lstnew(sphere));
	scene->m_camera = Camera();
	return (scene);
}

void printProgress(int y)
{
	int progress = (((float)(y) / (float)HEIGHT) * 100) + 1;
	if (progress < 100)
		printf("\033[A\33[2K\r %d%%\n", progress);
	else
		printf("\033[A\33[2K\r DONE.\n");
}
t_image *Render(scene_t *scene, void *mlx)
{
	t_image *image;
	image = initialize(mlx);

	int y = 0, x = 0;
	double xFact = 1.0 / (((double)WIDTH) / 2.0);
	double yFact = 1.0 / (((double)HEIGHT) / 2.0);
	y = 0;
	while (y < HEIGHT )
	{
		x = 0;
		// printProgress(y);
		while (x < WIDTH )
		{
			double normX = (((double)x) * xFact) - 1.0;
			double normY = (((double)y) * yFact) - 1.0;
			ray_t *ray = generate_ray(scene->m_camera, normX, normY);
			if (cast_ray(ray, scene))
				set_pixel(image, x, y, 1, 1, 1);
			else
			{
				set_pixel(image, x, y, .0, .0, .0);
			}
			x++;
		}
		y++;
	}
	return image;
}

int cast_ray(ray_t *ray, scene_t *scene)
{
	int valide_int = 0;
	t_list *tmp = scene->m_object_list;

	vector_t intPoint;
	vector_t localNormal;
	vector_t localColor;

	while (tmp)
	{
		valide_int = ((object_t *)tmp->content)->test_inter((object_t *)tmp->content, ray, &intPoint, &localNormal, &localColor);
		tmp = tmp->next;
	}
	if (valide_int)
		printf("valide_int : true \n");
	return (valide_int);
}
