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

int main(int ac, char **av, char **env)
{
    if (ac >= 2)
    {
        if (ft_strcmp(av[1], "echo") == 0)
            ft_echo(av);
        else if (ft_strcmp(av[1], "pwd") == 0)
            ft_pwd();
        else if (ft_strcmp(av[1], "env") == 0)
            ft_env(env);
        else
            {
                printf("Run it like ./a.out echo [input]\n");
                printf("Run it like ./a.out pwd\n");
            }

    }
    else
    {
        printf("run it like ./minishell echo [input]\n");
    }
    return (0);
}
