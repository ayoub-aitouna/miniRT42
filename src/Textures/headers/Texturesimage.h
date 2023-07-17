/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texturesimage.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:27:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 23:02:04 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURESIMAGE_H
# define TEXTURESIMAGE_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

t_textures	*new_img_texture(void *mlx_ptr, char *filename);

t_txtr_img	*load_img(void *mlx_ptr, char *filename);
t_vector	*get_rgb_color(t_textures *this, t_uv_cords cords);
t_vector	*get_shi_color(t_textures *this, t_uv_cords cords);
t_vector	*get_color(t_txtr_img *txtr_img, t_uv_cords cords);
#endif