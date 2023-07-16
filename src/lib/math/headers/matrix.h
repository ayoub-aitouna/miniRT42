/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:58 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 04:14:40 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "libtypes.h"
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

t_matrix	*create_matrix(int r, int c);
t_matrix	*mt_multiplication(t_matrix *mt1, t_matrix *mt2);
void		fill_mt(t_matrix *mt, double *values);
void		print_matrix(t_matrix *matrix);
t_matrix	*matrix(int rows, int cols, double *values);
double		determinant(t_matrix *mt);
t_matrix	*submatrix(t_matrix *mt, int row, int column);
double		minor(t_matrix *mt, int row, int column);
double		cofactor(t_matrix *mt, int row, int column);
t_matrix	*inverse(t_matrix *mt);
t_matrix	*transpose(t_matrix *mt);
void		set_to_indentity(t_matrix *mt);
t_matrix	*safe_matrix_multy(t_matrix *mt1, t_matrix *mt2);
void		delete_matrix(t_matrix *this);
#endif
