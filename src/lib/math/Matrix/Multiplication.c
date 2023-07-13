/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Multiplication.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:13:24 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/12 22:20:56 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"
#include "../headers/types.h"
#include <stdio.h>

matrix_t *mt_multiplication(matrix_t *mt1, matrix_t *mt2)
{
	matrix_t *result;
	int i;
	int j;
	int k;

	i = 0;
	if (!mt1 || !mt2 || mt1->cols != mt2->rows)
		return (NULL);
	result = create_matrix(mt1->rows, mt2->cols);
	while (i < mt1->rows)
	{
		k = 0;
		while (k < mt2->cols)
		{
			j = 0;
			while (j < mt1->cols)
			{
				result->matrix[i][k] += (mt1->matrix[i][j] * mt2->matrix[j][k]);
				j++;
			}
			k++;
		}
		i++;
	}
	return (result);
}

matrix_t *safe_matrix_multy(matrix_t *mt1, matrix_t *mt2)
{
	matrix_t *result;

	if (!mt1 || !mt2)
		return (NULL);
	result = mt_multiplication(mt1, mt2);
	delete_matrix(mt1);
	delete_matrix(mt2);
	if (!result)
		printf("error in safe mt \n");
	return (result);
}