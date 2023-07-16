/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gtfm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:11 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 06:58:16 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../headers/types.h"
#include "../headers/gtfm.h"
#include "../headers/matrix.h"
#include "../headers/vectormath.h"

t_matrix	*set_transform(t_vector *translation, t_vector *rotation,
		t_vector *scal)
{
	t_matrix	*result;

	if (!translation || !rotation || !scal)
	{
		printf("some thing null in set_transform \n");
		return (NULL);
	}
	result = NULL;
	result = safe_matrix_multy(translation_matrix(translation),
			rotation_matrix_x(rotation->x));
	result = safe_matrix_multy(result, rotation_matrix_y(rotation->y));
	result = safe_matrix_multy(result, rotation_matrix_z(rotation->z));
	result = safe_matrix_multy(result, scal_matrix(scal));
	return (result);
}

t_ray	*apply_transform(t_ray *input_ray, t_object *this, int dirFlag)
{
	t_ray	*output;

	output = malloc(sizeof(t_ray));
	output->point1 = apply_transform_vector(input_ray->point1, dirFlag, this);
	output->point2 = apply_transform_vector(input_ray->point2, dirFlag, this);
	output->m_lab = minus(output->point2, output->point1);
	return (output);
}

t_vector	*apply_transform_vector(t_vector *inputVector, int dirFlag,
		t_object *this)
{
	t_matrix	*tmp;
	double		*values;
	t_matrix	*resultmt;
	t_vector	*result;

	resultmt = NULL;
	values = (double []){inputVector->x, inputVector->y, inputVector->z, 1.0f};
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

void	set_lineartfm(t_object *this)
{
	t_matrix	*tmp;
	t_matrix	*inverse_tmp;
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

t_vector	*get_norm(t_object *this, t_vector *input_vector)
{
	t_matrix	*tmp;
	t_matrix	*resultmt;
	t_vector	*result;

	resultmt = NULL;
	tmp = matrix(3, 1, (double []){input_vector->x, input_vector->y,
			input_vector->z});
	resultmt = mt_multiplication(this->lineartfm, tmp);
	result = vector(resultmt->matrix[0][0], resultmt->matrix[1][0],
			resultmt->matrix[2][0]);
	delete_matrix(resultmt);
	delete_matrix(tmp);
	normalize(result);
	return (result);
}
