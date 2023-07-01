/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/30 01:22:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef matrix_H
# define matrix_H

# include "types.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

matrix_t	*create_matrix(int r, int c);
matrix_t	*mt_multiplication(matrix_t *mt1, matrix_t *mt2);
void		fill_mt(matrix_t *mt, double *values);
void		print_matrix(matrix_t *matrix);
matrix_t	*matrix(int rows, int cols, double *values);
double		determinant(matrix_t *mt);
matrix_t	*submatrix(matrix_t *mt, int row, int column);
double		minor(matrix_t *mt, int row, int column);
double		cofactor(matrix_t *mt, int row, int column);
matrix_t	*inverse(matrix_t *mt);
matrix_t	*transpose(matrix_t *mt);
void		set_to_indentity(matrix_t *mt);
matrix_t	*safe_matrix_multy(matrix_t *mt1, matrix_t *mt2);
void		delete_matrix(matrix_t *this);
#endif
