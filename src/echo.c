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
        if ((ft_strcmp(args[i], "-n") == 0))
        {
            is_n = 1;
            while (args[i] && (ft_strcmp(args[i], "-n") == 0))
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
        write(1, "\n", 1);
    return (0);
}
// int main(int ac, char **av)
// {
//     if (ac > 2)
//     {
//         if (ft_strcmp(av[1], "echo") == 0)
//             ft_echo(av);
//         else
//             printf("run it like ./a.out echo [input]\n");
//     }
//     printf("run it like ./a.out echo [input]\n");
//     return (0);
// }