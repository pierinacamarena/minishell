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
    printf("%s\n", getcwd(NULL, 0));
    return (0);
}

int ft_env(t_env_list *env)
{
    ft_print_list(env);
    return (1);
}

void    ft_exit(long long i, t_shell *shell)
{
    //free anything allocated once we are more advanced in the project :P
    ft_free_list(&shell->env);
    ft_free_list(&shell->exp);
    if (shell->new_env)
	{
        ft_free(shell->new_env);
	}
    ft_free(shell->cmds);
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}