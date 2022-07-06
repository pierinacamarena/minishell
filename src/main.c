/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 18:52:54 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 18:54:58 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av)
{
    if (ac > 2)
    {
        if (ft_strcmp(av[1], "echo") == 0)
            ft_echo(av);
        else
            printf("Run it like ./a.out echo [input]\n");
    }
    else
    {
        printf("run it like ./minishell echo [input]\n");
    }
    return (0);
}
