/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:48:10 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:50:23 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BASE_H
# define BASE_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

t_textures	*new_base_texture(void);

void		set_tfm(t_textures *this, t_vector2 *translation, t_vector2 *scal,
				double rotation);
t_uv_cords	*apply_transform_textures(t_textures *this, t_uv_cords *cords);
t_vector	*apply_bump_map_textures(t_textures *this, t_vector *org_normal,
				t_uv_cords cords);
void		*gb_mlx(void *mlx_ptr);
void		delete_textures(t_textures *this);
#endif
