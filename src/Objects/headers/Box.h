/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Box.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/28 05:24:16 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/28 05:24:38 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOX_H
# define BOX_H
# include "base.h"
object_t	*box(vector_t *translation, vector_t *rotation, vector_t *scal,
				vector_t *color);
#endif