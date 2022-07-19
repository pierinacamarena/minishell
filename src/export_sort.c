/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_sort.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/12 20:48:26 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/12 20:48:29 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t  array_size(char **arr)
{
    int len;

    len = 0;
    while (arr[len])
        len++;
    return (len);
}

void    ft_swap(char **a, char **b)
{
    char *temp;

    temp = *a;
    *a = *b;
    *b = temp;
}

int     not_sorted(char **env)
{
    int i;
    int size;

    i = 0;
    size = array_size(env);
    while (env[i] && env[i+1])
    {
        if (ft_strcmp(env[i], env[i+1]) > 0)
            return (1);
        i++;
    }
    if (ft_strcmp(env[size - 2], env[size - 1]) > 0)
    {
        printf("%s\n%s\n", env[size-2], env[size - 1]);
        return (1);
    }
    return (0);
}

void    print_double_array(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        printf("%s\n", str[i]);
        i++;
    }
}

char    **sorted_exp(char **env)
{
    char    **arr;
    int     i;
    int     size;

    i = 0;
    size = array_size(env);
    arr = (char **)malloc(sizeof(char *) * (size + 1));
    if (!arr)
        return (NULL);
    while (i < size)
    {
        arr[i] = ft_strdup(env[i]);
        i++;
    }
    arr[size] = NULL;
    while (not_sorted(arr) == 1)
    {
        i = 0;
        while (arr[i] && arr[i + 1])
        {
            if (ft_strcmp(arr[i], arr[i + 1]) > 0)
            {
                ft_swap(&arr[i], &arr[i + 1]);
            }
            i++;
        }
        if (ft_strcmp(arr[size - 2], arr[size - 1]) > 0)
            ft_swap(&arr[size - 2], &arr[size - 1]);
    }
    return (arr);
}
