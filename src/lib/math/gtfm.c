/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/08 18:22:15 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/types.h"
#include "headers/gtfm.h"
#include "headers/matrix.h"
#include "headers/vectormath.h"

matrix_t	*Set_transform(vector_t *translation, vector_t *rotation,
		vector_t *scal)
{
	matrix_t	*translation_matrix;
	matrix_t	*rotationMatriX;
	matrix_t	*rotationMatriY;
	matrix_t	*rotationMatriZ;
	matrix_t	*scalMatrix;
	matrix_t	*result;

	if (!translation || !rotation || !scal)
	{
		printf("some thing null in Set_transform \n");
		return (NULL);
	}
	// define a matrix for each component of the transform
	translation_matrix = create_matrix(4, 4);
	rotationMatriX = create_matrix(4, 4);
	rotationMatriY = create_matrix(4, 4);
	rotationMatriZ = create_matrix(4, 4);
	scalMatrix = create_matrix(4, 4);
	// populate these with probpriate values
	// first translation matri
	// [1,0,0,0]
	// [0,1,0,0]
	// [0,0,1,0]
	// [0,0,0,1]
	set_to_indentity(translation_matrix);
	set_to_indentity(rotationMatriX);
	set_to_indentity(rotationMatriY);
	set_to_indentity(rotationMatriZ);
	set_to_indentity(scalMatrix);
	translation_matrix->matrix[0][3] = translation->x;
	translation_matrix->matrix[1][3] = translation->y;
	translation_matrix->matrix[2][3] = translation->z;
	// [cos()	,-sin()	,0		,0]
	// [sin()	,cos()	,0		,0]
	// [0,		,0		,1		,0]
	// [0,		0,		0		,1]
	rotationMatriZ->matrix[0][0] = cos(rotation->z);
	rotationMatriZ->matrix[0][1] = -sin(rotation->z);
	rotationMatriZ->matrix[1][0] = sin(rotation->z);
	rotationMatriZ->matrix[1][1] = cos(rotation->z);
	// [cos()	,0		,sin()	,0]
	// [0		,1		,0		,0]
	// [-sin()	,0		,cos()	,0]
	// [0,		,0		,0		,1]
	rotationMatriY->matrix[0][0] = cos(rotation->y);
	rotationMatriY->matrix[0][2] = sin(rotation->y);
	rotationMatriY->matrix[2][0] = -sin(rotation->y);
	rotationMatriY->matrix[2][2] = cos(rotation->y);
	// [1		,0		,0		,0]
	// [0		,cos()	,-sin()	,0]
	// [0,		,sin()	,cos()	,0]
	// [0,		,0		,0		,1]
	rotationMatriX->matrix[1][1] = cos(rotation->x);
	rotationMatriX->matrix[1][2] = -sin(rotation->x);
	rotationMatriX->matrix[2][1] = sin(rotation->x);
	rotationMatriX->matrix[2][2] = cos(rotation->x);
	// And the scal matrex
	//  [S,0,0,0]
	//  [0,S,0,0]
	//  [0,0,S,0]
	//  [0,0,0,1]
	scalMatrix->matrix[0][0] = scal->x;
	scalMatrix->matrix[1][1] = scal->y;
	scalMatrix->matrix[2][2] = scal->z;
	// combine to give the  final transform matrix
	result = NULL;
	result = safe_matrix_multy(translation_matrix, rotationMatriX);
	result = safe_matrix_multy(result, rotationMatriY);
	result = safe_matrix_multy(result, rotationMatriZ);
	result = safe_matrix_multy(result, scalMatrix);
	return (result);
}

ray_t	*Apply_transform(ray_t *input_ray, object_t *this, int dirFlag)
{
	ray_t	*output;

	output = malloc(sizeof(ray_t));
	output->point1 = Apply_transform_vector(input_ray->point1, dirFlag, this);
	output->point2 = Apply_transform_vector(input_ray->point2, dirFlag, this);
	output->m_lab = minus(output->point2, output->point1);
	return (output);
}

vector_t	*Apply_transform_vector(vector_t *inputVector, int dirFlag,
		object_t *this)
{
	matrix_t	*tmp;
	double		*values;
	matrix_t	*resultmt;
	vector_t	*result;

	resultmt = NULL;
	values = (double[]){inputVector->x, inputVector->y, inputVector->z, 1.0f};
	tmp = create_matrix(4, 1);
	fill_mt(tmp, values);
	if (dirFlag)
		resultmt = mt_multiplication(this->fwd_tfm, tmp);
	else
		resultmt = mt_multiplication(this->bck_tfm, tmp);
	if (!resultmt)
	{
		delete_matrix(tmp);
		return (vector(0, 0, 0));
	}
	result = vector(resultmt->matrix[0][0], resultmt->matrix[1][0],
			resultmt->matrix[2][0]);
	delete_matrix(resultmt);
	delete_matrix(tmp);
	return (result);
}

void	set_lineartfm(object_t *this)
{
	matrix_t	*tmp;
	matrix_t	*inverse_tmp;
	int			i;
	int			j;

	this->lineartfm = NULL;
	tmp = create_matrix(3, 3);
	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			tmp->matrix[i][j] = this->fwd_tfm->matrix[i][j];
			j++;
		}
		i++;
	}
	inverse_tmp = inverse(tmp);
	this->lineartfm = transpose(inverse_tmp);
	delete_matrix(tmp);
	delete_matrix(inverse_tmp);
}

vector_t	*get_norm(object_t *this, vector_t *input_vector)
{
	matrix_t	*tmp;
	matrix_t	*resultmt;
	vector_t	*result;

	resultmt = NULL;
	tmp = matrix(3, 1, (double[]){input_vector->x, input_vector->y,
			input_vector->z});
	resultmt = mt_multiplication(this->lineartfm, tmp);
	result = vector(resultmt->matrix[0][0], resultmt->matrix[1][0],
			resultmt->matrix[2][0]);
	delete_matrix(resultmt);
	delete_matrix(tmp);
	normalize(result);
	return (result);
}
