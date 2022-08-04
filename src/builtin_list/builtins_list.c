/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:11 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/04 21:39:28 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(int *read_write_fds)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
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
		// write(read_write_fds[1], "=", 1);
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

int	ft_exit_list(t_shell *shell, t_pipeline *data)
{
	int	len;
	int	exit_atoi;

	len = len_cmds_list(data->command);
	if (len > 2)
	{
		write_error("exit: too many arguments");
		return (1);
	}
	ft_free_list(&shell->env);
	ft_free_list(&shell->exp);
	if (len == 1)
		exit(0);
	else
	{
		if (!is_digit_arg(data->command[1]))
		{
			free_commands_list(data);
			write_error("exit: numeric argument required");
			exit(2);
		}
		exit_atoi = ft_atoi(data->command[1]);
		if (data->command[1][0] == '-')
		{
			exit_code = exit_code + exit_atoi;
			free_commands_list(data);
			exit(exit_code);
		}
		free_commands_list(data);
		exit(exit_atoi);
	}
}
