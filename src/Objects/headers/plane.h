/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:23:12 by aaitouna          #+#    #+#             */
/*   Updated: 2023/07/16 07:03:09 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H
# include "Objectbase.h"

t_object	*plane(t_vector *translation, t_vector *rotation, t_vector *scal,
				t_vector *color);
#endif