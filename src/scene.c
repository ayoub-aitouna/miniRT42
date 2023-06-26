#include "headers/scene.h"

t_list	*Objects(void)
{
	t_list		*data;
	object_t	*sphere;
	object_t	*m_cylinder;
	object_t	*m_triangle;
	object_t	*plan;
	object_t	*m_plan;

	data = NULL;
	m_cylinder = cone(vector(0.0, 0.0, -1.5), vector(0, 0, 0), vector(1.f, 1.f,
				1.f), vector(0.04, 0.78, 0.94));
	/*	
	m_triangle = triangle(vector(1.5, 0.0, -0.8), vector(0.0, .0f, -0.5708),
			vector(.8, .5, .5), vector(255 / 255.0f, 215 / 255.0f, 0));
	plan = plane(vector(.0, 0.0, 1), vector(0.0, 0, 0), vector(4.5, 4.0, 1.0),
			vector(.8, .3, 1.0));
	m_plan = plane(vector(.0, 1.5, 1), vector(-1 * HALFPI, 0, 0), vector(4.5,
				4.0, 1.0), vector(.04, .78, .94));
	sphere = create_sphere(vector(-1.5, -2.0, 0.0), vector(0, 0, 0), vector(.5f,
				.5f, .5f), vector(139.0f / 255.0f, .0, .0));
*/
	// push_back(&data, ft_lstnew(plan));
	// push_back(&data, ft_lstnew(m_plan));
	// push_back(&data, ft_lstnew(sphere));
	push_back(&data, ft_lstnew(m_cylinder));
	// push_back(&data, ft_lstnew(m_triangle));
	return (data);
}

t_list	*LightSorces(void)
{
	t_list	*data;

	data = NULL;
	push_back(&data, ft_lstnew(new_light(vector(-3.f, -5.f, -5.f), vector(1.0,
						1.0, 1.0), 1.0)));
	// push_back(&data, ft_lstnew(new_light(vector(0.f, -5.f, -2.f),
	// 										vector(1.0, 1.0, .0), 1.0)));
	// push_back(&data, ft_lstnew(new_light(vector(1.5f, -5.f, -2.f),
	// 										vector(.0, 1.0, .0), 1.0)));
	return (data);
}

void	setupCamera(scene_t *this)
{
	this->m_camera = Camera(.75f, 1.0f, (double)WIDTH / (double)HEIGHT);
	SetPosition(this->m_camera, vector(.0, -8.0, -2.0));
	SetUp(this->m_camera, vector(.0, .0, .1));
	Setloockat(this->m_camera, vector(.0, .0, 1));
	calculat_geometry(this->m_camera);
}

scene_t	*Scene(void)
{
	scene_t	*scene;

	scene = malloc(sizeof(scene_t));
	scene->m_object_list = Objects();
	scene->m_light_list = LightSorces();
	setupCamera(scene);
	scene->ambient_light_factor = (vector_t){.x = (255.f / 255.f) * 0.2f,
												.y = (255.f / 255.f) * 0.2f,
												.z = (255.f / 255.f) * 0.2f};
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

t_image	*Render(scene_t *scene)
{
	t_image		*image;
	int			y;
	double		xFact;
	double		yFact;
	double		normX;
	double		normY;
	ray_t		*ray;
	vector_t	c_intersection_point;
	object_t	*c_object;
	vector_t	c_norm;
	vector_t	c_color;
	int			x;
	vector_t	*color;

	image = initialize();
	y = 0;
	x = 0;
	xFact = 1.0 / (((double)WIDTH) / 2.0);
	yFact = 1.0 / (((double)HEIGHT) / 2.0);
	y = 0;
	c_object = NULL;
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
				color = c_object->material->calculat_color(scene, &c_norm,
						&c_intersection_point, &c_color, c_object, ray);
				set_pixel(image, x, y, color->x, color->y, color->z);
				free(color);
			}
			else
				set_pixel(image, x, y, 0, 0, 0);
			delete_ray(ray);
			x++;
		}
		// exit(0);
		y++;
	}
	return (image);
}

int	cast_ray(ray_t *ray, scene_t *scene, vector_t *c_int_point,
		object_t **c_object, vector_t *c_norm, vector_t *c_color)
{
	int			valide_int;
	int			found_int;
	t_list		*tmp;
	vector_t	intPoint;
	vector_t	localNormal;
	vector_t	localColor;
	object_t	*cur_object;
	vector_t	*dist_vector;
	double		min_dist;
	double		dist;

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

void	deleteScene(scene_t *this)
{
	if (this)
	{
		delete_object_list(this->m_object_list);
		delete_light_list(this->m_light_list);
		deleteCamera(this->m_camera);
		free(this);
	}
}