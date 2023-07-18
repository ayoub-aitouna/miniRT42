/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scenesObjects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 00:29:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/18 00:31:33 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/scene.h"

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
	ww = new_img_texture(mlx, "./assets/ww.xpm", "./assets/ww.xpm");
	brick = new_img_texture(mlx, "./assets/ganges_river_pebbles.xpm", "./assets/ganges_river_pebbles_disp.xpm");
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
	set_up_material_configurations(sphere, 0.0, 0.0, 0.0, 0.0, brick);
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
