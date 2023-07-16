/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TransformationMatrices.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 03:37:59 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/types.h"
#include "../headers/gtfm.h"
#include "../headers/matrix.h"
#include "../headers/vectormath.h"

/**
 * @brief rotation matrix at axices Y
 *  [cos()	,0		,sin()	,0]
 *  [0		,1		,0		,0]
 *  [-sin()	,0		,cos()	,0]
 *  [0,		,0		,0		,1]
 */
t_matrix	*rotation_matrix_y(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[0][0] = cos(angle);
	rotationmatrix->matrix[0][2] = sin(angle);
	rotationmatrix->matrix[2][0] = -sin(angle);
	rotationmatrix->matrix[2][2] = cos(angle);
	return (rotationmatrix);
}

/**
 * @brief rotation matrix at axices X
 *  [1		,0		,0		,0]
 *  [0		,cos()	,-sin()	,0]
 *  [0,		,sin()	,cos()	,0]
 *  [0,		,0		,0		,1]
 */
t_matrix	*rotation_matrix_x(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[1][1] = cos(angle);
	rotationmatrix->matrix[1][2] = -sin(angle);
	rotationmatrix->matrix[2][1] = sin(angle);
	rotationmatrix->matrix[2][2] = cos(angle);
	return (rotationmatrix);
}

/**
 * @brief rotation matrix at axices z
 *  [cos()	,-sin()	,0		,0]
 *  [sin()	,cos()	,0		,0]
 *  [0,		,0		,1		,0]
 *  [0,		0,		0		,1]
 */
t_matrix	*rotation_matrix_z(double angle)
{
	t_matrix	*rotationmatrix;

	rotationmatrix = create_matrix(4, 4);
	set_to_indentity(rotationmatrix);
	rotationmatrix->matrix[0][0] = cos(angle);
	rotationmatrix->matrix[0][1] = -sin(angle);
	rotationmatrix->matrix[1][0] = sin(angle);
	rotationmatrix->matrix[1][1] = cos(angle);
	return (rotationmatrix);
}

t_matrix	*translation_matrix(t_vector *translation)
{
	t_matrix	*translationmatrix;

	translationmatrix = create_matrix(4, 4);
	set_to_indentity(translationmatrix);
	translationmatrix->matrix[0][3] = translation->x;
	translationmatrix->matrix[1][3] = translation->y;
	translationmatrix->matrix[2][3] = translation->z;
	return (translationmatrix);
}

/**
 * @brief Scal matrix
 *  [S,0,0,0]
 *  [0,S,0,0]
 *  [0,0,S,0]
 *  [0,0,0,1]
 */
t_matrix	*scal_matrix(t_vector *scal)
{
	t_matrix	*scalmatrix;

	scalmatrix = create_matrix(4, 4);
	set_to_indentity(scalmatrix);
	scalmatrix->matrix[0][0] = scal->x;
	scalmatrix->matrix[1][1] = scal->y;
	scalmatrix->matrix[2][2] = scal->z;
	return (scalmatrix);
}
