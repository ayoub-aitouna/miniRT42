#ifndef LIB_H
#define LIB_H
#include "stdlib.h"

typedef struct list
{
    void *content;
    struct list *next;
} t_list;

void push_back(t_list **lst, t_list *node);
void ft_lstiter(t_list *lst, void (*f)(void *));
t_list *ft_lstnew(void *content);
int ft_lstsize(t_list *lst);
#endif
