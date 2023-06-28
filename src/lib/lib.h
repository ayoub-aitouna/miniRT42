/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitouna <aaitouna@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 23:22:29 by aaitouna          #+#    #+#             */
/*   Updated: 2023/06/27 23:22:29 by aaitouna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
#define LIB_H
#include "stdlib.h"
#include "math/headers/types.h"
typedef struct list
{
    void *content;
    struct list *next;
} t_list;

void push_back(t_list **lst, t_list *node);
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstnew(void *content);
int ft_lstsize(t_list *lst);
void free_list(void **ptrs, int size);

#endif
