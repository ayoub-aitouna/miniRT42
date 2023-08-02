/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_base.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/02 11:42:00 by clyamani          #+#    #+#             */
/*   Updated: 2023/08/02 11:42:20 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headers/base.h"

void	delete_txture_img(t_txtr_img *img)
{
	if (img)
	{
		if (img->img)
			free(img->img);
		free(img);
	}
}

void	delete_textures(t_textures *this)
{
	if (this)
	{
		if (this->tfm)
			delete_matrix(this->tfm);
		if (this->txtr_img)
			delete_txture_img(this->txtr_img);
		if (this->surface_hieght_info)
			delete_txture_img(this->surface_hieght_info);
		free(this);
	}
}
