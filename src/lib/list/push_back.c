/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_back.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:21:52 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:21:53 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

void push_back(t_list **lst, t_list *new)
{
    t_list *temp;

    temp = *lst;
    if (!*lst)
    {
        *lst = new;
        return;
    }
    while (temp)
    {
        if ((temp)->next == NULL)
            break;
        temp = (temp)->next;
    }
    (temp)->next = new;
}