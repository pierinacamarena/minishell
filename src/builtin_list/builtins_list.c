/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:11 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/07 13:57:36 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(int *read_write_fds, t_shell *shell)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		pwd = ft_getenv(shell->env, "PWD");
		if (pwd == NULL)
			return (0);
		pwd = ft_strdup(pwd);
		if (pwd == NULL)
			free_exit(-1, shell, NULL, HIST | ENV);
	}
	write(read_write_fds[1], pwd, ft_strlen(pwd));
	write(read_write_fds[1], "\n", 1);
	free(pwd);
	return (0);
}

int	ft_env(t_env_list *env, int *read_write_fds)
{
	while (env != NULL)
	{
		write(read_write_fds[1], env->node->key, ft_strlen(env->node->key));
		if (env->node->content != NULL)
			write(read_write_fds[1], env->node->content, \
			ft_strlen(env->node->content));
		write(read_write_fds[1], "\n", 1);
		env = env->next;
	}
	return (0);
}

int	is_digit_arg(char *s)
{
	int	i;

	i = -1;
	while (s && s[++i])
	{
		if (s[0] == '-')
			s++;
		if (!ft_isdigit(s[i]))
			return (0);
	}
	return (1);
}

void	exit_helper(t_pipeline *data, t_shell *shell)
{
	int	exit_atoi;

	if (!is_digit_arg(data->command[1]))
	{
		write_error("exit: numeric argument required\n");
		free_exit(2, shell, data, ENV | CMD | HIST);
	}
	exit_atoi = ft_atoi(data->command[1]);
	if (data->command[1][0] == '-')
	{
		g_exit_code = g_exit_code + exit_atoi;
		free_exit(g_exit_code, shell, data, ENV | CMD | HIST);
	}
	free_exit(exit_atoi, shell, data, ENV | CMD | HIST);
}

int	ft_exit_list(t_shell *shell, t_pipeline *data)
{
	int	len;

	len = len_cmds_list(data->command);
	if (len > 2)
	{
		write_error("exit: too many arguments\n");
		return (1);
	}
	ft_free_list(&shell->env);
	ft_free_list(&shell->exp);
	if (len == 1)
		free_exit(0, shell, data, ENV | CMD | HIST);
	else
		exit_helper(data, shell);
	return (0);
}
