/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   VecMath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 01:13:03 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/13 01:17:49 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/vectormath.h"

/**
 * r = l - 2(l.n).n
 * r & l & n : are vectors
 */
vector_t *Reflection_vector(vector_t *l, vector_t *n)
{
    vector_t   *r;
    double ln;

    ln = dot(*l, *n);
    r = ms_minus(l, num_muliplication(n, 2 * ln), 1);
    normalize(r);
    return (r);
}

double vector_distance(vector_t *u, vector_t *v)
{
    vector_t *result;
    double distance = 0.0f;

    result = minus(u, v);
    distance = vector_lenght(*result);
    free(result);
    return (distance);
}

vector_t *from_mt_to_vt(matrix_t mt)
{
    if (mt.cols != 3 || mt.rows != 1)
        return (NULL);
    return (vector(mt.matrix[0][0], mt.matrix[0][1], mt.matrix[0][2]));
}
