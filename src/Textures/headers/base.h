/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:48:10 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 17:05:58 by aaitouna         ###   ########.fr       */
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

void		set_tfm(t_textures *this, vector2_t *translation, vector2_t *scal,
				double rotation);
t_uv_cords	*apply_transform(t_textures *this,
							t_uv_cords *cords);
vector_t	*apply_bump_map_textures(t_textures *this, vector_t *org_normal,
				t_uv_cords cords);
void		delete_textures(t_textures *this);
#endif
