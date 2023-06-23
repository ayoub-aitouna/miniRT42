#include "headers/scene.h"

scene_t *Scene(void)
{
	scene_t *scene;
	object_t *sphere;
	object_t *m_triangle;
	object_t *plan;

	scene = malloc(sizeof(scene_t));
	scene->m_object_list = NULL;
	scene->m_light_list = NULL;
	sphere = create_sphere(vector(-1, -1.0, -0.8), vector(0, 0, 0), vector(.5, .5, .5), vector(.9, .0, .2));
	m_triangle = triangle(vector(0.0, -1.0, -0.8), vector(-1.5708, .0f, -0.5708), vector(.8, .5, .5), vector(1, 1, 1));
	plan = plane(vector(0, 0, 0.0), vector(0, 0, 0), vector(4, 4, 1.0), vector(.1, .5, .2));

	push_back(&scene->m_object_list, ft_lstnew(plan));
	push_back(&scene->m_object_list, ft_lstnew(sphere));
	push_back(&scene->m_object_list, ft_lstnew(m_triangle));

	push_back(&scene->m_light_list, ft_lstnew(new_light(vector(.0, -10.0, -5.0),
														vector(1.0, 1.0, 1.0), 1.0)));
	scene->m_camera = Camera(0.75f, 1.0f, (16.0f / 9.0f));
	SetPosition(scene->m_camera, vector(.0, -5.0, -1.0));
	SetUp(scene->m_camera, vector(.0, .0, .1));
	Setloockat(scene->m_camera, vector(.0, .0, .0));
	calculat_geometry(scene->m_camera);
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
							   vector_t *initPoint, vector_t *base_color, object_t *cur_object)
{
	vector_t Color;
	t_list *tmp;
	double intensity;
	int validIlum;
	double r;
	double g;
	double b;

	validIlum = 0;
	r = 0;
	g = 0;
	b = 0;
	tmp = scene->m_light_list;
	while (tmp)
	{
		validIlum = calculatIlumination(tmp->content, localNormal, initPoint,
										&intensity, &Color, scene, cur_object);
		if (validIlum)
		{
			r += Color.x * intensity;
			g += Color.y * intensity;
			b += Color.z * intensity;
		}
		tmp = tmp->next;
	}
	return (vector(r * base_color->x, g * base_color->y, b * base_color->z));
}

t_image *Render(scene_t *scene)
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
	vector_t *color;

	image = initialize();
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
			if (cast_ray(ray, scene, &c_intersection_point, &c_object, &c_norm,
						 &c_color))
			{
				color = CalculatDiffuseColor(scene, &c_norm,
											 &c_intersection_point, &c_color, c_object);
				set_pixel(image, x, y, color->x, color->y, color->z);
			}
			else
				set_pixel(image, x, y, 0.0, 0.0, 0.0);

			x++;
		}
		y++;
	}
	return (image);
}

int cast_ray(ray_t *ray, scene_t *scene, vector_t *c_int_point, void **c_object,
			 vector_t *c_norm, vector_t *c_color)
{
	int valide_int;
	int found_int;
	t_list *tmp;
	vector_t intPoint;
	vector_t localNormal;
	vector_t localColor;
	object_t *cur_object;
	vector_t *dist_vector;
	double min_dist;
	double dist;

	cur_object = NULL;
	valide_int = 0;
	found_int = 0;
	tmp = scene->m_object_list;
	min_dist = 1e6;
	dist = 0.0;
	while (tmp)
	{
		cur_object = ((object_t *)tmp->content);
		if (cur_object != NULL)
		{
			valide_int = cur_object->test_inter(cur_object, ray, &intPoint,
												&localNormal, &localColor);
			if (valide_int)
			{
				found_int = 1;
				dist_vector = minus(&intPoint, ray->point1);
				dist = vector_lenght(*dist_vector);
				free(dist_vector);
				if (dist < min_dist)
				{
					min_dist = dist;
					*c_color = localColor;
					*c_norm = localNormal;
					*c_int_point = intPoint;
					*c_object = cur_object;
				}
			}
		}
		tmp = tmp->next;
	}
	return (found_int);
}
