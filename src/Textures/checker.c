/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:51:46 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:48:55 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/checker.h"

t_textures	*new_texture(t_vector color_1, t_vector color_2)
{
	t_textures	*t;

	t = new_base_texture();
	t->color_1 = color_1;
	t->color_2 = color_2;
	t->get_color = get_ch_color;
	t->tfm = NULL;
	return (t);
}

t_vector	*get_ch_color(t_textures *this, t_uv_cords cords)
{
	t_uv_cords	*new_cords;
	int			uv_sum;

	new_cords = apply_transform_textures(this, &cords);
	uv_sum = (int)floor(new_cords->u) + (int)floor(new_cords->v);
	free(new_cords);
	if (uv_sum % 2 == 0)
		return (copy_vector(this->color_1));
	return (copy_vector(this->color_2));
}
