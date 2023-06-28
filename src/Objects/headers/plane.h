/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:12 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:23:12 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
#define PLANE_H

#include "base.h"
object_t *plane(vector_t *translation, vector_t *rotation,
                vector_t *scal, vector_t *color);
#endif