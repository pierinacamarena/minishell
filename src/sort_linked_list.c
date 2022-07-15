#include "../includes/minishell.h"

void    swap_export(t_exp_list *prev, t_exp_list *less, t_exp_list *more, t_exp_list **first)
{
    less->next = more->next;
    more->next = less;
    if (less == *first)
        *first = more;
    else
        prev->next = more;
}

void bubble_sort(t_exp_list **first)
{
    bool        sort;
    t_exp_list *curr;
    t_exp_list *prev;

    if (*first == NULL)
        return ;

    curr = *first;
    prev = curr;
    sort = true;
    while (sort)
    {
        sort = false;
        while (curr->next)
        {
            if (ft_strcmp(curr->content, curr->next->content) > 0)
            {
                swap_export(prev, curr, curr->next, first);
                sort = true;
            }
            prev = curr;
            curr = curr->next;
        }
    }
}
