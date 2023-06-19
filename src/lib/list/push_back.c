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