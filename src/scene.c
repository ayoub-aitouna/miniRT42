/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:53 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/17 20:18:20 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/scene.h"

t_list	*objects(void *mlx)
{
	t_list		*data;
	t_object	*sphere;
	t_object	*sphere2;
	t_object	*sphere3;
	t_object	*m_torus;
	t_object	*floor;
	t_object	*image;
	t_textures	*checker;
	t_textures	*ww;
	t_textures	*brick;

	data = NULL;
	(void)mlx;
	checker = new_texture((t_vector){1.0, 1.0, 1.0}, (t_vector){0.2, 0.2, 0.2});
	set_tfm(checker, &(t_vector2){.x = 0, .y = 0}, &(t_vector2){.x = 16,
		.y = 16}, 0);
	ww = new_img_texture(mlx, "./assets/ww.xpm");
	brick = new_img_texture(mlx, "./assets/brick.xpm");
	floor = plane(vector(.0, 0.0, 1.0), vector(0.0, 0, 0), vector(16.0, 16.0,
				1.0), vector(1, 1, 1.0));
	image = plane(vector(0.0, 5.0, -0.75), vector(-PI / 2.0, 0.0, 0.0),
			vector(1.75, 1.75, 1.0), vector(1, 1, 1.0));
	sphere = create_sphere(vector(-2.0, -2.0, 0.25), vector(HALFPI, HALFPI,
				HALFPI), vector(0.75, 0.75, 0.75), vector(1.0, 0.2, 0.2));
	sphere2 = create_sphere(vector(-2.0, -0.5, 0.25), vector(0.0, 0.0, 0.0),
			vector(0.75, 0.75, 0.75), vector(0.2, 1.0, 0.2));
	sphere3 = create_sphere(vector(-2.0, -1.25, -1.0), vector(0.0, 0.0, 0.0),
			vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));
	m_torus = torus(vector(2.0, -1.25, 0.25), vector(HALFPI, 0.0, 0.0),
			vector(0.75, 0.75, 0.75), vector(0.2, 0.2, 1.0));
	
	set_up_material_configurations(floor, 0.25, 32.0, 0.0, 0.0, checker);
	set_up_material_configurations(image, 0.00, 0.00, 0.0, 0.0, ww);
	set_up_material_configurations(sphere, 0.25, 32.0, 0.0, 0.0, brick);
	set_up_material_configurations(sphere2, 0.55, 32.0, 0.3, 1.33, NULL);
	set_up_material_configurations(sphere3, 0.35, 32.0, 0.0, 0.0, NULL);
	set_up_material_configurations(m_torus, 0.25, 32.0, 0.75, 1.333, brick);

	push_back(&data, ft_lstnew(floor));
	push_back(&data, ft_lstnew(sphere));
	push_back(&data, ft_lstnew(sphere2));
	push_back(&data, ft_lstnew(sphere3));
	push_back(&data, ft_lstnew(m_torus));
	push_back(&data, ft_lstnew(image));
	return (data);
}

void	set_up_material_configurations(t_object *this, double reflection,
		double shininess, double translution, double bending_index,
		t_textures *texture)
{
	this->material->reflection_coefficient = reflection;
	this->material->shininess_coefficient = shininess;
	this->material->transparency_coefficient = translution;
	this->material->reflactive_index = bending_index;
	this->textures = texture;
}

t_list	*light_source(void)
{
	t_list	*data;

	data = NULL;
	push_back(&data, ft_lstnew(new_light(vector(3.0, -10.0, -5.0), vector(1.0,
					1.0, 1.0), 4.0)));
	push_back(&data, ft_lstnew(new_light(vector(0.0, -10.0, -5.0), vector(1.0,
					1.0, 1.0), 2.0)));
	return (data);
}

void	set_upcamera(t_scene *this)
{
	this->m_camera = camera(1, 1, (double)WIDTH / (double)HEIGHT);
	set_position(this->m_camera, vector(2.0, -5.0, 0.25));
	set_up(this->m_camera, vector(0.0, 0.0, 1.0));
	set_loock_at(this->m_camera, vector(0.0, 0.0, 0.0));
	calculat_geometry(this->m_camera);
}

t_scene	*scene(void *mlx, void *mlx_win)
{
	t_scene	*scene;

	(void)mlx_win;
	scene = malloc(sizeof(t_scene));
	scene->m_object_list = objects(mlx);
	scene->m_light_list = light_source();
	set_upcamera(scene);
	scene->ambient_light_factor = (t_vector){.x = (255.f / 255.f) * 0.2f,
		.y = (255.f / 255.f) * 0.2f, .z = (255.f / 255.f) * 0.2f};
	return (scene);
}

void	print_progress(int y)
{
	int	progress;

	progress = (((float)(y) / (float)HEIGHT) * 100) + 1;
	if (progress < 100)
		printf("\033[A\33[2K\r %d%%\n", progress);
	else
		printf("\033[A\33[2K\r DONE.\n");
}

void	render_line(t_scene *scene, t_image *image, int y, t_vector fact)
{
	int				x;
	t_ray			*ray;
	t_propretries	prop;
	t_object		*c_object;
	t_vector		*color;

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
			set_pixel(image, x, y, &(t_vector){.x = 0, .y = 0, .z = 0});
		delete_ray(ray);
		x++;
	}
}

t_image	*render(t_scene *scene, void *mlx, void *mlx_win)
{
	t_image		*image;
	int			y;
	t_vector	fact;

	(void)mlx;
	(void)mlx_win;
	image = initialize();
	fact = (t_vector){.x = 1.0 / (((double)WIDTH) / 2.0), .y = 1.0
		/ (((double)HEIGHT) / 2.0)};
	y = 0;
	while (y < HEIGHT)
	{
		print_progress(y);
		render_line(scene, image, y, fact);
		y++;
	}
	return (image);
}

int	check_n_set_dist(t_propretries *prop, t_ray *ray, double *min_dist)
{
	double	dist;

	dist = vector_distance(&prop->int_point, ray->point1);
	if (dist < *min_dist)
	{
		*min_dist = dist;
		return (TRUE);
	}
	return (FALSE);
}

int	cast_ray(t_ray *ray, t_scene *scene, t_propretries *c_prop,
		t_object **c_object)
{
	int				found_int;
	t_list			*tmp;
	t_propretries	prop;
	double			min_dist;

	found_int = 0;
	tmp = scene->m_object_list;
	min_dist = 1e6;
	while (tmp)
	{
		if (((t_object *)tmp->content) != NULL)
		{
			if (((t_object *)tmp->content)->test_inter(((t_object *)tmp->content),
					ray, &prop))
			{
				found_int = 1;
				if (check_n_set_dist(&prop, ray, &min_dist))
					update_values(c_prop, c_object, &prop,
						((t_object *)tmp->content));
			}
		}
		tmp = tmp->next;
	}
	return (found_int);
}

void	update_values(t_propretries *c_prop, t_object **c_object,
		t_propretries *prop, t_object *cur_object)
{
	*c_prop = *prop;
	*c_object = cur_object;
}

void	deletescene(t_scene *this)
{
	if (this)
	{
		delete_object_list(this->m_object_list);
		delete_light_list(this->m_light_list);
		deletecamera(this->m_camera);
		free(this);
	}
}
