/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:46 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:21:47 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

t_list *ft_lstnew(void *content)
{
    t_list *node;

    node = malloc(sizeof(t_list));
    if (!node)
        return (0);
    node->content = content;
    node->next = NULL;
    return (node);
}