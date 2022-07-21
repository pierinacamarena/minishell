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

static int num_args(char **args)
{
    int num;

    num = 0;
    while (args[num] != NULL)
        num++;
    return (num);
}

int ft_isn(char *str)
{
    int i;
    int len;

    i = 1;
    len = ft_strlen(str);
    if (str[0] == '-')
    {
        while (str[i] == 'n' && i < len)
            i++;
        if (i == len)
            return (1);
        else
            return (0);
    }
    else
        return (0);
}

int ft_echo(char **args)
{
    int len;
    int is_n;
    int i;

    i = 1;
    is_n = 0;
    len = num_args(args);
    // still need to handle the case of echo -nnnnnnn -n -n -n -n abc
    // still need to handle the case of echo ${numbers}
    if (len > 1)
    {
        //while ((ft_strcmp(args[i], "-n") == 0) && args[1])
        while ((ft_isn(args[i]) == 1) && args[1])
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
