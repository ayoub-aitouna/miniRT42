/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 11:27:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 08:49:37 by aaitouna         ###   ########.fr       */
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

t_checker_textures	*new_img_texture(void *mlx_ptr, char *filename);

void				load_img(t_checker_textures *this, void *mlx_ptr,
						char *filename);

vector_t			*get_color(t_checker_textures *this, t_uv_cords cords);
#endif
