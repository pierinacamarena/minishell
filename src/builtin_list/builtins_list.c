/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:11 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/04 12:45:30 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int ft_pwd(int *read_write_fds)
{
	char *pwd;

	pwd = getcwd(NULL, 0);
	write(read_write_fds[1], pwd, ft_strlen(pwd));
    //printf("%s\n", pwd);
	free(pwd);
    return (0);
}

//added this function to print on right fd
int	ft_env(t_env_list *env, int *read_write_fds)
{
	while (env != NULL)
	{
		write(read_write_fds[1], env->node->key, ft_strlen(env->node->key));
		write(read_write_fds[1], "=", 1);
		write(read_write_fds[1], env->node->content, ft_strlen(env->node->content));
		write(read_write_fds[1], "\n", 1);
		env = env->next;
	}
	return (1);
}

void    ft_exit_list(long long i, t_shell *shell, t_pipeline *data)
{
    ft_free_list(&shell->env);
    ft_free_list(&shell->exp);
	free_commands_list(data);
    if (i <= INT_MAX || i >= INT_MIN)
        exit(i);
}
