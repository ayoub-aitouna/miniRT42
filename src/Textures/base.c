/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/02 11:42:22 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/base.h"

t_textures	*new_base_texture(void)
{
	t_textures	*base;

	base = malloc(sizeof(t_textures));
	base->tfm = NULL;
	base->get_surface_hieght = NULL;
	base->surface_hieght_info = NULL;
	base->txtr_img = NULL;
	base->get_color = NULL;
	return (base);
}

void	set_tfm(t_textures *this, t_vector2 *translation, t_vector2 *scal,
		double rotation)
{
	t_matrix	*tmt;
	t_matrix	*rmt;
	t_matrix	*smt;

	tmt = matrix(3, 3, (double []){1.0, 0.0, translation->x,
			0.0, 1.0, translation->y, 0.0, 0.0, 1.0});
	rmt = matrix(3, 3, (double []){cos(rotation), -sin(rotation),
			0.0, sin(rotation), cos(rotation), 0.0, 0.0, 0.0, 1.0});
	smt = matrix(3, 3, (double []){scal->x, 0.0, 0.0, 0.0,
			scal->y, 0.0, 0.0, 0.0, 1.0});
	this->tfm = safe_matrix_multy(safe_matrix_multy(tmt, rmt), smt);
}

t_uv_cords	*apply_transform_textures(t_textures *this, t_uv_cords *cords)
{
	t_matrix	*result;
	t_matrix	*uv;
	t_uv_cords	*r;

	if (!this->tfm)
		return (cords);
	uv = matrix(3, 1, (double []){cords->u, cords->v, 0.0});
	result = mt_multiplication(this->tfm, uv);
	r = malloc(sizeof(t_uv_cords));
	r->u = result->matrix[0][0];
	r->v = result->matrix[1][0];
	delete_matrix(result);
	delete_matrix(uv);
	return (r);
}

t_vector	*apply_bump_map_textures(t_textures *this, t_vector *org_normal,
		t_uv_cords cords)
{
	t_vector	*color;
	t_vector	*scaled_vec;
	double		displacement;

	if (!this->get_surface_hieght)
		return (org_normal);
	color = this->get_surface_hieght(this, cords);
	displacement = (color->x + color->y + color->z) / 3;
	displacement = ((displacement * 2) - 1);
	free(color);
	scaled_vec = num_muliplication(org_normal, displacement);
	return (ms_addition(org_normal, scaled_vec, 2));
}
