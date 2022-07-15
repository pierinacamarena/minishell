#include <stdio.h>
#include <stdlib.h>

struct  s_node
{
    int data;
    struct s_node *next;
}       t_node;

t_node *swap(t_node *n1, t_node *n2)
{
    t_node *temp;

    temp = n2->next;
    n2->next = n1;
    n1->next = tmp;
    return (n2);
}

int bubble_sort(t_node **head, int count)
{
    t_node **h;
    int     i;
    int     j;
    int     swapped;

    for(i = 0; i <= count; i++)
    {
        h = head;
        swapped = 0;
        for (j = 0; j < count- i - 1; j++)
        {
            t_node *p1;
            t_node *p2;

            p1 = *h;
            p2 = p1->next;
        }
    }
}