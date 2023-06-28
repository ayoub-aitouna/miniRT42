/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cone.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:06 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:23:07 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONE_H
#define CONE_H
#include "base.h"
#include "cylinder.h"
object_t *cone(vector_t *translation, vector_t *rotation,
               vector_t *scal, vector_t *color);
#endif