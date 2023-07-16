/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 01:32:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:47:22 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_H
# define CHECKER_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"
# include "base.h"

t_textures	*new_texture(t_vector color_1, t_vector color_2);
t_vector	*get_ch_color(t_textures *this, t_uv_cords cords);

#endif
