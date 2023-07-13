/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Inverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:16:56 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/12 22:17:45 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"
#include "../headers/types.h"
#include <stdio.h>

/**
 * 1: |a b|
 * 2: |c d|
 * det = ad - bc;
 */
double determinant(matrix_t *mt)
{
	double d;
	int column_index;

	column_index = 0;
	d = 0;
	if (mt->cols != mt->rows)
		return (0);
	if (mt->cols == 2 || mt->rows == 2)
		d = (mt->matrix[0][0] * mt->matrix[1][1]) - (mt->matrix[0][1] * mt->matrix[1][0]);
	else
	{
		while (column_index < mt->cols)
		{
			d += mt->matrix[0][column_index] * cofactor(mt, 0, column_index);
			column_index++;
		}
	}
	return (d);
}

matrix_t *submatrix(matrix_t *mt, int row, int column)
{
	int i;
	int j;
	int filer_col_index;
	int filer_row_index;
	matrix_t *new_matrix;

	if (mt->rows <= 1 || mt->cols <= 1)
		return (mt);
	new_matrix = create_matrix(mt->rows - 1, mt->rows - 1);
	i = 0;
	filer_col_index = 0;
	filer_row_index = 0;
	while (i < mt->rows)
	{
		j = 0;
		filer_col_index = 0;
		if (i == row)
		{
			i++;
			continue;
		}
		while (j < mt->cols)
		{
			if (j != column)
			{
				new_matrix->matrix[filer_row_index][filer_col_index] = mt->matrix[i][j];
				filer_col_index++;
			}
			j++;
		}
		filer_row_index++;
		i++;
	}
	return (new_matrix);
}

double minor(matrix_t *mt, int row, int column)
{
	matrix_t *sub;
	double m_determinant;

	sub = submatrix(mt, row, column);
	m_determinant = determinant(sub);
	delete_matrix(sub);
	return (m_determinant);
}

double cofactor(matrix_t *mt, int row, int column)
{
	int sign;

	sign = 1;
	if ((row + column) % 2 != 0)
		sign = -1;
	return (sign * minor(mt, row, column));
}

matrix_t *inverse(matrix_t *mt)
{
	matrix_t *Invers;
	int row_index;
	int col_index;
	double c;
	double dt;

	dt = determinant(mt);
	if (dt == 0)
		return (NULL);
	Invers = create_matrix(mt->rows, mt->cols);
	row_index = 0;
	while (row_index < mt->rows)
	{
		col_index = 0;
		while (col_index < mt->cols)
		{
			c = cofactor(mt, row_index, col_index);
			Invers->matrix[col_index][row_index] = (c / dt);
			col_index++;
		}
		row_index++;
	}
	return (Invers);
}
