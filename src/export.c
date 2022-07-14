/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
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
    int comp;
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
        printf("%s\n", i, str[i]);
        i++;
    }
}

int main (int ac, char **av, char **env)
{
    (void)ac;
    (void)av;
    int     sort;
    int     i;
    int     j;
    int     size;
    char    **arr;

    i = 0;
    size = array_size(env);
    arr = (char **)malloc(sizeof(char *) * size + 1);
    if (!arr)
        return (-1);
    while(i < size)
    {
        arr[i] = ft_strdup(env[i]);
        i++;
    }
    arr[i] = NULL;
    size = array_size(arr);
    ft_print_env(arr);
    printf("@@@@@@@@@@@@\n");
    i = 0;
    j = 0;
    {
        while (not_sorted(arr) == 1 && j < 200)
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
            j++;
        }
        if (ft_strcmp(arr[size - 2], arr[size - 1]) > 0)
            ft_swap(&arr[size - 2], &arr[size - 1]);
    }
    ft_print_env(arr);
    return (0);
}

int ft_export(t_shell *shell)
{
    
    return (0);
}