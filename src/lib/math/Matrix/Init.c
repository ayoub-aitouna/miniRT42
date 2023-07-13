/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:21:31 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/12 22:21:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/matrix.h"
#include "../headers/types.h"
#include <stdio.h>

matrix_t *matrix(int rows, int cols, double *values)
{
    matrix_t *mt;

    mt = create_matrix(rows, cols);
    fill_mt(mt, values);
    return (mt);
}

void fill_mt(matrix_t *mt, double *values)
{
    int k;

    k = 0;
    for (int i = 0; i < mt->rows; i++)
    {
        for (int j = 0; j < mt->cols; j++)
            mt->matrix[i][j] = values[k++];
    }
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
