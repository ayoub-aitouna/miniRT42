/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 10:17:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 17:24:39 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/Texturesimage.h"

t_textures	*new_img_texture(void *mlx_ptr, char *filename)
{
	t_textures	*t;

	t = new_base_texture();
	t->get_color = get_color;
	load_img(t, mlx_ptr, filename);
	return (t);
}

void	load_img(t_textures *this, void *mlx_ptr, char *filename)
{
	this->img = NULL;
	this->img = malloc(sizeof(t_data));
	this->img->img = mlx_xpm_file_to_image(mlx_ptr, filename, &this->img_width,
			&this->img_height);
	if (!this->img->img)
	{
		printf("error img null name is : <%s>  \n", filename);
		exit(127);
	}
	this->img->addr = mlx_get_data_addr(this->img->img,
			&this->img->bits_per_pixel, &this->img->line_length,
			&this->img->endian);
}

vector_t	*get_color(t_textures *this, t_uv_cords cords)
{
	unsigned int	all;
	char			*dst;
	t_uv_cords		mapping_cords;

	mapping_cords = (t_uv_cords){
		.u = (this->img_width - 1) - (floor((cords.u + 1) * ((this->img_width
							- 1) / 2.f))),
		.v = (this->img_height - 1) - (floor((double)(cords.v + 1)
					* ((this->img_height - 1) / 2.f)))};
	dst = this->img->addr + ((int)mapping_cords.v * this->img->line_length
			+ (int)mapping_cords.u * (this->img->bits_per_pixel / 8));
	all = *(unsigned int *)dst;
	return (vector((all >> 16 & 255) / 255.f, ((all >> 8) & 255) / 255.f,
			(all & 255) / 255.f));
}
