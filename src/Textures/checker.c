/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:51:46 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 06:44:23 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/checker.h"

t_checker_textures	*new_texture(vector_t color_1, vector_t color_2)
{
	t_checker_textures	*t;

	t = new_base_texture();
	t->color_1 = color_1;
	t->color_2 = color_2;
	t->get_color = get_ch_color;
	t->tfm = NULL;
	return (t);
}
vector_t	*get_ch_color(t_checker_textures *this, t_uv_cords cords)
{
	t_uv_cords	*new_cords;

	new_cords = apply_transform(this, &cords);
	if (((int)floor(new_cords->u) + (int)floor(new_cords->v)) % 2 == 0)
		return (copy_vector(this->color_1));
	return (copy_vector(this->color_2));
}
