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

int num_args(char **args)
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
        while (((ft_strcmp(args[i], "-e") == 0) || (ft_strcmp(args[i], "-E") == 0) ) && args[1])
            i++;
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
