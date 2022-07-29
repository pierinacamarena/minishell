/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:22:14 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 17:22:16 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_pwd(void)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
    printf("%s\n", pwd);
	free(pwd);
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
    ft_free(shell->cmds);
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}