/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectormath.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:06 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/31 21:58:42 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORMATH_H
# define VECTORMATH_H

# include "libtypes.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

void		print_vector(t_vector v);
double		vector_lenght(t_vector v);
double		vector_lenght2(t_vector v);
t_vector	*normalized(t_vector *v);
double		normalize(t_vector *v);
t_vector	*vector(double x, double y, double z);
t_vector2	*vec2(double x, double y);
t_vector	*copy_vector(t_vector v);
t_vector	*equal(t_vector *target, t_vector *v);
t_vector	*minus(t_vector *target, t_vector *v);
t_vector	*addition(t_vector *target, t_vector *v);
t_vector	*muliplication(t_vector *target, t_vector *v);
t_vector	*num_muliplication(t_vector *target, double num);
t_vector	*division(t_vector *target, t_vector *v);
t_vector	*num_division(t_vector *target, double l);
double		dot(t_vector v, t_vector u);
t_vector	*cross(t_vector v, t_vector u);
t_vector	*from_mt_to_vt(t_matrix mt);
t_vector	*normalized_sub(t_vector *u, t_vector *v);

/*************************************************/
/***********   Memory Safe Funtions     **********/
/*************************************************/
void		free_at_index(void *ptr1, void *ptr2, int index);
t_vector	*ms_minus(t_vector *target, t_vector *v, int free_at);
t_vector	*ms_addition(t_vector *target, t_vector *v, int free_at);
t_vector	*ms_division(t_vector *target, t_vector *v, int free_at);
t_vector	*ms_muliplication(t_vector *target, t_vector *v, int free_at);
t_vector	*ms_num_muliplication(t_vector *target, double num);
t_vector	*ms_normalized_sub(t_vector *u, t_vector *v, int free_at);
/*************************************************/
/***********   Advance vectors Math     **********/
/*************************************************/

double		vector_distance(t_vector *u, t_vector *v);
t_vector	*reflection_vector(t_vector *l, t_vector *n);

#endif
