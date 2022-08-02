/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:11 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 19:40:22 by pcamaren         ###   ########.fr       */
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

void    ft_exit_list(long long i, t_shell *shell, t_pipeline *data)
{
    //free anything allocated once we are more advanced in the project :P
    ft_free_list(&shell->env);
    ft_free_list(&shell->exp);
	free_commands_list(data);
	//call function that will clean the linked list
	//list_clear(&data);
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}