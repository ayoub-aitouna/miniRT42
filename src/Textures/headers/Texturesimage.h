/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Texturesimage.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:27:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:47:36 by aaitouna         ###   ########.fr       */
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

void		load_img(t_textures *this, void *mlx_ptr, char *filename);

t_vector	*get_color(t_textures *this, t_uv_cords cords);
#endif
