#ifndef PARSING_H
# define PARSING_H
# include "../../get_next_line/get_next_line.h"
# include "../../headers/main.h"
# include "../../lib/math/headers/vectormath.h"
# include <ctype.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
void			err(char *msg);
void			check_for_parametres(char **list, t_parsing *pars);
t_list			*ReadFile(char *fileName);
t_scene_object	*handle_line(char *line);
int				double_ptr_size(char **str);
t_vector		*vec_range_check(char **list, double max, double min);
int				f_in_range(double value, double max, double min);
#endif