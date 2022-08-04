/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:22:14 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/04 12:22:03 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

int ft_echo(char **args, int *read_write_fds)
{
    int len;
    int is_n;
    int i;

    i = 1;
    is_n = 0;
    len = num_args(args);
	if (len == 1)
	{
		write(read_write_fds[1], "\n", 1);
		//printf("\n");
		return (0);
	}
    if (len > 1)
    {
        while ((ft_isn(args[i]) == 1) && args[1])
        {
            is_n = 1;
            i++;
        }
        while (args[i] && i < (len - 1))
        {
			write(read_write_fds[1], args[i], ft_strlen(args[i]));
			write(read_write_fds[1], " ", 1);
            //printf("%s ",args[i]);
            i++;
        }
		write(read_write_fds[1], args[i], ft_strlen(args[i]));
        //printf("%s", args[i]);
    }
    if (is_n == 0)
		write(read_write_fds[1], "\n", 1);
        //printf("\n");
    return (0);
}
