/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libtypes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clyamani <clyamani@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:04 by aaitouna          #+#    #+#             */
/*   Updated: 2023/08/03 22:05:20 by clyamani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBTYPES_H
# define LIBTYPES_H

# ifndef PI
#  define PI 3.1415926f
# endif

# ifndef HALFPI
#  define HALFPI 1.5707963f
# endif

# ifndef FALSE
#  define FALSE 0
# endif

# ifndef TRUE
#  define TRUE 1
# endif

# ifndef FRWRD
#  define FRWRD 1
# endif

# ifndef BCKWRD
#  define BCKWRD 0
# endif

# ifndef MAX_V
#  define MAX_V 100e6
# endif

# ifndef EPSILON
#  define EPSILON 1e-21
# endif

typedef struct matrix
{
	int				rows;
	int				cols;
	double			**matrix;
}					t_matrix;

typedef struct vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct vector2
{
	float	x;
	float	y;
}	t_vector2;

typedef t_vector	t_point;

#endif
