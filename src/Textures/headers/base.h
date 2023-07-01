/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 00:48:10 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/01 08:49:32 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURESBASE_H
# define TEXTURESBASE_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"

t_checker_textures	*new_base_texture(void);

void				set_tfm(t_checker_textures *this, vector2_t *translation,
						vector2_t *scal, double rotation);
t_uv_cords	*apply_transform(t_checker_textures *this,
							t_uv_cords *cords);
#endif
