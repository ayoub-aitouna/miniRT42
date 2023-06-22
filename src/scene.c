
#include "headers/scene.h"

scene_t *Scene(void)
{
	scene_t *scene;
	object_t *sphere;

	scene = malloc(sizeof(scene_t));
	scene->m_object_list = NULL;
	scene->m_light_list = NULL;
	sphere = create_sphere(vector(0, 0, 0), vector(0, 0, 0), vector(1, 1, 1),
						   vector(.9, .5, .2));
	push_back(&scene->m_light_list, ft_lstnew(new_light(vector(10, -10, -5),
	 vector(1, 1, 1), 1)));
	push_back(&scene->m_object_list, ft_lstnew(sphere));
	scene->m_camera = Camera();
	return (scene);
}

void printProgress(int y)
{
	int progress;

	progress = (((float)(y) / (float)HEIGHT) * 100) + 1;
	if (progress < 100)
		printf("\033[A\33[2K\r %d%%\n", progress);
	else
		printf("\033[A\33[2K\r DONE.\n");
}

vector_t *CalculatDiffuseColor(scene_t *scene, vector_t *localNormal,
							   vector_t *initPoint, vector_t *base_color)
{
	vector_t *diffuse_color;
	double intensity;
	int validIlum = 0;
	double r = 0, g = 0, b = 0;
	vector_t Color;
	t_list *tmp = scene->m_light_list;
	while (tmp)
	{
		validIlum = calculatIlumination(tmp->content, localNormal, initPoint, &intensity, &Color);
		if (validIlum)
		{
			r += Color.x * intensity;
			g += Color.y * intensity;
			b += Color.z * intensity;
			printf("found ilumination {%f, %f, %f} , intensity %f\n\n", r,g,b, intensity);
		}
		tmp = tmp->next;
	}
	
	return vector(r * base_color->x, g * base_color->y, b * base_color->z);
}

t_image *Render(scene_t *scene, void *mlx)
{
	t_image *image;
	int y;
	double xFact;
	double yFact;
	double normX;
	double normY;
	ray_t *ray;
	vector_t c_intersection_point;
	void *c_object;
	vector_t c_norm;
	vector_t c_color;
	int x;

	image = initialize(mlx);
	y = 0;
	x = 0;
	xFact = 1.0 / (((double)WIDTH) / 2.0);
	yFact = 1.0 / (((double)HEIGHT) / 2.0);
	y = 0;
	double scal = 0;
	while (y < HEIGHT)
	{
		x = 0;
		printProgress(y);
		while (x < WIDTH)
		{
			normX = (((double)x) * xFact) - 1.0;
			normY = (((double)y) * yFact) - 1.0;
			ray = generate_ray(scene->m_camera, normX, normY);
			if (cast_ray(ray, scene, &c_intersection_point, &c_object, &c_norm,
						 &c_color))
			{
				// vector_t *color = CalculatDiffuseColor(scene, &c_norm, &c_intersection_point, &c_color);
				// set_pixel(image, x, y, color->x, color->y, color->z);
				set_pixel(image, x, y,scal,scal,scal);

			}
			else
			{
				set_pixel(image, x, y, .0, .0, .0);
			}
			x++;
		}
		scal += 60;
		y++;
	}
	return (image);
}

int cast_ray(ray_t *ray, scene_t *scene, vector_t *c_int_point,
			 void **c_object, vector_t *c_norm, vector_t *c_color)
{
	int valide_int;
	t_list *tmp;
	vector_t intPoint;
	vector_t localNormal;
	vector_t localColor;
	object_t *cur_object = NULL;
	valide_int = 0;
	tmp = scene->m_object_list;
	while (tmp)
	{
		cur_object = ((object_t *)tmp->content);
		if (cur_object == NULL)
		{
			tmp = tmp->next;
			continue;
		}
		valide_int = cur_object->test_inter(cur_object, ray, &intPoint, &localNormal, &localColor);
		if (valide_int)
		{
			*c_color = localColor;
			*c_norm = localColor;
			*c_int_point = intPoint;
			*c_object = cur_object;
		}
		tmp = tmp->next;
	}
	return (valide_int);
}
