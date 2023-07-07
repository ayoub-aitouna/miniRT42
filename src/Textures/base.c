/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:01 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/07 08:49:04 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/base.h"

t_textures *new_base_texture(void)
{
	t_textures *base;

	base = malloc(sizeof(t_textures));
	base->tfm = NULL;
	return (base);
}

void set_tfm(t_textures *this, vector2_t *translation,
			 vector2_t *scal, double rotation)
{
	matrix_t *tmt;
	matrix_t *rmt;
	matrix_t *smt;

	tmt = matrix(3, 3, (double[]){1.0, 0.0, translation->x, 0.0, 1.0, translation->y, 0.0, 0.0, 1.0});
	rmt = matrix(3, 3, (double[]){cos(rotation), -sin(rotation), 0.0, sin(rotation), cos(rotation), 0.0, 0.0, 0.0, 1.0});
	smt = matrix(3, 3, (double[]){scal->x, 0.0, 0.0, 0.0, scal->y, 0.0, 0.0, 0.0, 1.0});
	this->tfm = safe_matrix_multy(safe_matrix_multy(tmt, rmt), smt);
}

t_uv_cords *apply_transform(t_textures *this, t_uv_cords *cords)
{
	matrix_t *result;
	matrix_t *uv;
	t_uv_cords *r;

	if (!this->tfm)
		return (cords);
	uv = matrix(3, 1, (double[]){cords->u, cords->v, 0.0});
	result = mt_multiplication(this->tfm, uv);
	r = malloc(sizeof(t_uv_cords));
	r->u = result->matrix[0][0];
	r->v = result->matrix[1][0];
	delete_matrix(result);
	delete_matrix(uv);
	return (r);
}

vector_t *apply_bump_map_textures(t_textures *this, vector_t *org_normal, t_uv_cords cords)
{
	vector_t *color;
	double displacement;
	color = this->get_color(this, cords);
	double avg = (color->x + color->y + color->z) / 3;
	displacement = (avg * 2) - 1;
	return  ms_num_muliplication(org_normal, displacement);
}
