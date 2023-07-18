/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:17:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/17 23:25:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Texturesimage.h"

t_textures	*new_img_texture(void *mlx_ptr, char *filename, char *dsp_filename)
{
	t_textures	*t;

	t = new_base_texture();
	t->get_color = get_rgb_color;
	t->get_surface_hieght = get_shi_color;
	t->txtr_img = load_img(mlx_ptr, filename);
	t->surface_hieght_info = load_img(mlx_ptr, dsp_filename);
	return (t);
}

t_txtr_img	*load_img(void *mlx_ptr, char *filename)
{
	t_txtr_img	*txtr_img;

	txtr_img = malloc(sizeof(t_txtr_img));
	txtr_img->img = NULL;
	txtr_img->img = malloc(sizeof(t_data));
	txtr_img->img->img = mlx_xpm_file_to_image(mlx_ptr, filename,
			&txtr_img->img_width, &txtr_img->img_height);
	if (!txtr_img->img->img)
	{
		printf("error img null name is : <%s>  \n", filename);
		exit(127);
	}
	txtr_img->img->addr = mlx_get_data_addr(txtr_img->img->img,
			&txtr_img->img->bits_per_pixel,
			&txtr_img->img->line_length, &txtr_img->img->endian);
	return (txtr_img);
}

t_vector	*get_rgb_color(t_textures *this, t_uv_cords cords)
{
	return (get_color(this->txtr_img, cords));
}

t_vector	*get_shi_color(t_textures *this, t_uv_cords cords)
{
	return (get_color(this->surface_hieght_info, cords));
}

t_vector	*get_color(t_txtr_img *txtr_img, t_uv_cords cords)
{
	unsigned int	all;
	char			*dst;
	t_uv_cords		mapping_cords;
	double			u;
	double			v;

	u = (txtr_img->img_width - 1) - (floor((cords.u + 1)
				* ((txtr_img->img_width - 1) / 2.f)));
	v = (txtr_img->img_height - 1)
		- (floor((double)(cords.v + 1)
				*((txtr_img->img_height - 1) / 2.f)));
	mapping_cords = (t_uv_cords){.u = u, .v = v};
	dst = txtr_img->img->addr
		+ ((int)mapping_cords.v * txtr_img->img->line_length
			+ (int)mapping_cords.u * (txtr_img->img->bits_per_pixel / 8));
	all = *(unsigned int *)dst;
	return (vector((all >> 16 & 255) / 255.f, ((all >> 8) & 255) / 255.f,
			(all & 255) / 255.f));
}
