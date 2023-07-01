#ifndef TEXTURECHECKER_H
# define TEXTURECHECKER_H
# include "../../Lights/headers/pointlight.h"
# include "../../headers/main.h"
# include "../../headers/ray.h"
# include "../../headers/types.h"
# include "../../lib/math/headers/matrix.h"
# include "../../lib/math/headers/vectormath.h"
# include "base.h"

t_checker_textures	*new_texture(vector_t color_1, vector_t color_2);
vector_t			*get_ch_color(t_checker_textures *this, t_uv_cords cords);

#endif
