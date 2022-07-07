/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:22:14 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 17:22:16 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* 
Command that outputs the strings that are passed to it as arguments
*/

static int num_args(char **args)
{
    int num;

    num = 0;
    while (args[num] != NULL)
        num++;
    return (num);
}

int ft_echo(char **args)
{
    int len;
    int is_n;
    int i;

    i = 2;
    is_n = 0;
    len = num_args(args);
    if (len > 1)
    {
        while ((ft_strcmp(args[i], "-n") == 0) && args[1])
        {
            is_n = 1;
            i++;
        }
        while (args[i] && i < (len - 1))
        {
            printf("%s ",args[i]);
            i++;
        }
        printf("%s", args[i]);
    }
    if (is_n == 0)
        printf("\n");
    return (0);
}

int ft_pwd(void)
{
    printf("%s\n", getenv("PWD"));
    return (0);
}

int ft_env(char **env)
{
    int i;

    i = 0;
    while(env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}

void    ft_exit(long long i)
{
    //free anything allocated once we are more advanced in the project :P
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}