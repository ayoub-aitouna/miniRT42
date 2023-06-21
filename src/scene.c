
#include "headers/scene.h"

scene_t	*Scene(void)
{
	scene_t		*scene;
	object_t	*sphere;

	scene = malloc(sizeof(scene_t));
	scene->m_object_list = NULL;
	sphere = create_sphere(vector(0, 0, 0), vector(0, 0, 0), vector(1, 1, 1),
			vector(.9, .5, .2));
	push_back(&scene->m_object_list, ft_lstnew(sphere));
	scene->m_camera = Camera();
	return (scene);
}

void	printProgress(int y)
{
	int	progress;

	progress = (((float)(y) / (float)HEIGHT) * 100) + 1;
	if (progress < 100)
		printf("\033[A\33[2K\r %d%%\n", progress);
	else
		printf("\033[A\33[2K\r DONE.\n");
}

t_image	*Render(scene_t *scene, void *mlx)
{
	t_image		*image;
	int			y;
	double		xFact;
	double		yFact;
	double		normX;
	double		normY;
	ray_t		*ray;
	vector_t	*c_intersection_point;
	void		*c_object;
	vector_t	*c_norm;
	vector_t	*c_color;
	int			x;

	c_color = vector(0, 0, 0);
	image = initialize(mlx);
	y = 0;
	x = 0;
	xFact = 1.0 / (((double)WIDTH) / 2.0);
	yFact = 1.0 / (((double)HEIGHT) / 2.0);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		printProgress(y);
		while (x < WIDTH)
		{
			normX = (((double)x) * xFact) - 1.0;
			normY = (((double)y) * yFact) - 1.0;
			ray = generate_ray(scene->m_camera, normX, normY);
			if (cast_ray(ray, scene, c_intersection_point, c_object, c_norm,
					c_color))
				set_pixel(image, x, y, c_color->x, c_color->y, c_color->z);
			else
			{
				set_pixel(image, x, y, .0, .0, .0);
			}
			x++;
		}
		y++;
	}
	return (image);
}

int	cast_ray(ray_t *ray, scene_t *scene, vector_t *c_intersection_point,
		void *c_object, vector_t *c_norm, vector_t *c_color)
{
	int			valide_int;
	t_list		*tmp;
	vector_t	intPoint;
	vector_t	localNormal;
	vector_t	localColor;

	valide_int = 0;
	tmp = scene->m_object_list;
	while (tmp)
	{
		valide_int = ((object_t *)tmp->content)->test_inter((object_t *)tmp->content,
				ray, &intPoint, &localNormal, &localColor);
		if (valide_int)
			*c_color = *((object_t *)tmp->content)->base_color;
		tmp = tmp->next;
	}
	return (valide_int);
}
