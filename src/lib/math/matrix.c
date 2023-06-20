#include "headers/matrix.h"
#include "headers/types.h"
#include <stdio.h>

void print_matrix(matrix_t *matrix)
{
	int i;
	int j;

	if (!matrix)
		return;
	i = 0;
	printf("[ \n");
	while (i < matrix->rows)
	{
		j = 0;
		printf("\t[ ");
		while (j < matrix->cols)
		{
			printf(" %f  %c", matrix->matrix[i][j], j < (matrix->cols - 1) ? ',' : ' ');
			j++;
		}
		printf("],\n");
		i++;
	}
	printf("]\n");
}

matrix_t *matrix(int rows, int cols, double *values)
{
	matrix_t *mt;

	mt = create_matrix(rows, cols);
	fill_mt(mt, values);
	return (mt);
}

void fill_mt(matrix_t *mt, double *values)
{
	int k = 0; // index of current value
	for (int i = 0; i < mt->rows; i++)
	{
		for (int j = 0; j < mt->cols; j++)
			mt->matrix[i][j] = values[k++];
	}
}

matrix_t *from_vector_to_matrix(vector_t vt, matrix_t mt)
{
	matrix_t *new_mt;

	new_mt = create_matrix(1, 3);
	new_mt->matrix[0][0] = vt.x;
	new_mt->matrix[0][1] = vt.y;
	new_mt->matrix[0][2] = vt.z;
	return (new_mt);
}

double *create_cols(int c)
{
	int i;
	double *new_col;

	i = 0;
	new_col = malloc(c * sizeof(double));
	while (i < c)
		new_col[i++] = .0;
	return (new_col);
}

matrix_t *create_matrix(int rows, int cols)
{
	matrix_t *new_mt;
	int i;
	double **mt;

	if (rows <= 0 || cols <= 0)
		return (NULL);
	new_mt = malloc(sizeof(matrix_t));
	i = 0;
	new_mt->rows = rows;
	new_mt->cols = cols;
	mt = malloc(sizeof(double *) * rows);
	while (i < rows)
		mt[i++] = create_cols(cols);
	new_mt->matrix = mt;
	return (new_mt);
}

matrix_t *mt_multiplication(matrix_t *mt1, matrix_t *mt2)
{
	matrix_t *result;
	int i;
	int j;
	int k;

	i = 0;
	if (!mt1 || !mt2 || mt1->cols != mt2->rows)
	{
		printf("error trying to multiplicat 2 matrixes \n");
		return (NULL);
	}
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
		return 0;
	if (mt->cols == 2 || mt->rows == 2)
		d = (mt->matrix[0][0] * mt->matrix[1][1]) - (mt->matrix[0][1] * mt->matrix[1][0]);
	else
	{
		while (column_index < mt->cols)
		{
			// printf("%.1f += %.1f * %.1f ", d, mt->matrix[0][column_index], cofactor(mt, 0, column_index));
			d += mt->matrix[0][column_index] * cofactor(mt, 0, column_index);
			column_index++;
		}
		// printf("\n");
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
	return (determinant(submatrix(mt, row, column)));
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

void set_to_indentity(matrix_t *mt)
{
	int i = 0, j = 0;
	while (i < mt->rows)
	{
		j = 0;
		while (j < mt->cols)
		{
			if (i == j)
				mt->matrix[i][j] = 1;
			j++;
		}
		i++;
	}
}