#include "lib.h"

void free_list(void **ptrs, int size)
{
    int i = 0;
    if (!ptrs)
        return;
    while (i < size)
    {
        if (ptrs[i])
            free(ptrs[i]);
        i++;
    }
}