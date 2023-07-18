/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:23:04 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/18 00:25:43 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/scene.h"

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
