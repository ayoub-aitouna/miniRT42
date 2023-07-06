/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/06 10:52:58 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/scene.h"

t_list *Objects(void *mlx)
{
	t_list *data;
	data = NULL;

	// **************************************************************************************
	// Create some spheres.
	// **************************************************************************************
	object_t *sphere;
	object_t *sphere2;
	object_t *sphere3;
	object_t *sphere4;

	object_t *floor;
	object_t *image;

	// **************************************************************************************
	// Create some textures.
	// **************************************************************************************
	t_textures *checker;
	t_textures *ww;
	t_textures *brick;

	checker = new_texture((vector_t){1.0, 1.0, 1.0}, (vector_t){0.2, 0.2, 0.2});
	set_tfm(checker, &(vector2_t){.x = 0, .y = 0}, &(vector2_t){.x = 16, .y = 16},
			0);
	ww = new_img_texture(mlx, "./assets/ww.xpm");
	brick = new_img_texture(mlx, "./assets/brick.xpm");
	// **************************************************************************************
	// Create and setup objects.
	// **************************************************************************************
	floor = plane(vector(.0, 0.0, 1.0), vector(0.0, 0, 0), vector(16.0, 16.0, 1.0), vector(1, 1, 1.0));
	image = plane(vector(0.0, 5.0, -0.75), vector(-PI / 2.0, 0.0, 0.0), vector(1.75, 1.75, 1.0), vector(1, 1, 1.0));
	sphere = create_sphere(vector(-2.0, -2.0, 0.25), vector(0.0, 0.0, 0.0), vector(0.75, 0.75, 0.75), vector(1.0, 0.2, 0.2));
	sphere2 = create_sphere(vector(-2.0, -0.5, 0.25), vector(0.0, 0.0, 0.0), vector(0.75, 0.75, 0.75), vector(0.2, 1.0, 0.2));
	sphere3 = create_sphere(vector(-2.0, -1.25, -1.0), vector(0.0, 0.0, 0.0), vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));
	sphere4 = cone(vector(2.0, -1.25, 0.25), vector(0.0, 0.0, 0.0), vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));

	// **************************************************************************************
	// Setup the materials.
	// **************************************************************************************
	floor->material->reflection_coefficient = .25;
	floor->material->reflactive_index = 0;
	floor->textures = checker;

	image->textures = ww;

	sphere->material->reflection_coefficient = 0.2;
	sphere->material->shininess_coefficient = 32.0;
	sphere->textures = brick;

	sphere2->material->reflection_coefficient = 0.8;
	sphere2->material->shininess_coefficient = 32.0;

	sphere3->material->reflection_coefficient = 0.8;
	sphere3->material->shininess_coefficient = 32.0;

	sphere4->material->reflection_coefficient = .25;
	sphere4->material->shininess_coefficient = 32.0;
	sphere4->material->transparency_coefficient = .75;
	sphere4->material->reflactive_index = 1.333;

	// **************************************************************************************
	// Put the objects into the scene.
	// **************************************************************************************
	push_back(&data, ft_lstnew(floor));
	push_back(&data, ft_lstnew(sphere));
	// push_back(&data, ft_lstnew(sphere2));
	// push_back(&data, ft_lstnew(sphere3));
	// push_back(&data, ft_lstnew(sphere4));
	// push_back(&data, ft_lstnew(image));
	return (data);
}

// **************************************************************************************
// setup the lights.
// **************************************************************************************
t_list *LightSorces(void)
{
	t_list *data;

	data = NULL;
	push_back(&data, ft_lstnew(new_light(vector(3.0, -10.0, -5.0), vector(1.0, 1.0, 1.0), 4.0)));
	push_back(&data, ft_lstnew(new_light(vector(0.0, -10.0, -5.0), vector(1.0, 1.0, 1.0), 2.0)));
	return (data);
}

void setupCamera(scene_t *this)
{
	this->m_camera = Camera(1, 1, (double)WIDTH / (double)HEIGHT);
	SetPosition(this->m_camera, vector(2.0, -5.0, 0.25));
	SetUp(this->m_camera, vector(0.0, 0.0, 1.0));
	Setloockat(this->m_camera, vector(0.0, 0.0, 0.0));
	calculat_geometry(this->m_camera);
}

scene_t *Scene(void *mlx, void *mlx_win)
{
	scene_t *scene;

	(void)mlx_win;
	scene = malloc(sizeof(scene_t));
	scene->m_object_list = Objects(mlx);
	scene->m_light_list = LightSorces();
	setupCamera(scene);
	// **************************************************************************************
	// Setup ambient lightling.
	// **************************************************************************************
	scene->ambient_light_factor = (vector_t){.x = (255.f / 255.f) * 0.2f,
											 .y = (255.f / 255.f) * 0.2f,
											 .z = (255.f / 255.f) * 0.2f};
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

void render_line(scene_t *scene, t_image *image, int y, vector_t fact)
{
	int x;
	ray_t *ray;
	propretries_t prop;
	object_t *c_object;
	vector_t *color;

	c_object = NULL;
	x = 0;
	while (x < WIDTH)
	{
		ray = generate_ray(scene->m_camera, (((double)x) * fact.x) - 1.0,
						   (((double)y) * fact.y) - 1.0);
		if (cast_ray(ray, scene, &prop, &c_object))
		{
			color = c_object->material->calculat_color(scene, &prop,
													   (t_color_params){c_object, ray, 0});
			set_pixel(image, x, y, color);
			free(color);
		}
		else
			set_pixel(image, x, y, &(vector_t){.x = 0, .y = 0, .z = 0});
		delete_ray(ray);
		x++;
	}
}

t_image *Render(scene_t *scene, void *mlx, void *mlx_win)
{
	t_image *image;
	int y;
	vector_t fact;

	(void)mlx;
	(void)mlx_win;
	image = initialize();
	fact = (vector_t){.x = 1.0 / (((double)WIDTH) / 2.0), .y = 1.0 / (((double)HEIGHT) / 2.0)};
	y = 0;
	while (y < HEIGHT)
	{
		printProgress(y);
		render_line(scene, image, y, fact);
		y++;
	}
	return (image);
}

int check_n_set_dist(propretries_t *prop, ray_t *ray, double *min_dist)
{
	double dist;

	dist = vector_distance(&prop->int_point, ray->point1);
	if (dist < *min_dist)
	{
		*min_dist = dist;
		return (TRUE);
	}
	return (FALSE);
}

int cast_ray(ray_t *ray, scene_t *scene, propretries_t *c_prop,
			 object_t **c_object)
{
	int found_int;
	t_list *tmp;
	propretries_t prop;
	double min_dist;

	found_int = 0;
	tmp = scene->m_object_list;
	min_dist = 1e6;
	while (tmp)
	{
		if (((object_t *)tmp->content) != NULL)
		{
			if (((object_t *)tmp->content)->test_inter(((object_t *)tmp->content), ray, &prop))
			{
				found_int = 1;
				if (check_n_set_dist(&prop, ray, &min_dist))
					update_values(c_prop, c_object, &prop,
								  ((object_t *)tmp->content));
			}
		}
		tmp = tmp->next;
	}
	return (found_int);
}

void update_values(propretries_t *c_prop, object_t **c_object,
				   propretries_t *prop, object_t *cur_object)
{
	*c_prop = *prop;
	*c_object = cur_object;
}

void deleteScene(scene_t *this)
{
	if (this)
	{
		delete_object_list(this->m_object_list);
		delete_light_list(this->m_light_list);
		deleteCamera(this->m_camera);
		free(this);
	}
}
