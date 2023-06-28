/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:04 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:22:04 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
#define TYPES_H

#ifndef PI
#define PI 3.1415926f
#endif

#ifndef HALFPI
#define HALFPI  1.5707963f
#endif

#ifndef EPSILON
#define EPSILON 1e-21f
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif


#ifndef FRWRD
#define FRWRD 1
#endif

#ifndef BCKWRD
#define BCKWRD 0
#endif

#ifndef MAX_V
#define MAX_V 100e6
#endif

typedef struct matrix{
	int rows;
	int cols;
	double **matrix;
} matrix_t;

typedef struct vector
{
	float x, y, z;
} vector_t;

typedef struct vector2{
	float x,y;
} vector2_t;

typedef		vector_t point_t;

#endif
