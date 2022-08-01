/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:25:32 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 01:39:38 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     is_builtin_list(t_list *data)
{
    if (ft_strcmp(data->args[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(data->args[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(data->args[0], "env") == 0)
        return (1);
    else if (ft_strcmp(data->args[0], "exit") == 0)
        return (1);
    else if (ft_strcmp(data->args[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(data->args[0], "export") == 0)
        return (1);
    else if(ft_strcmp(data->args[0], "unset") == 0)
        return (1);
    return (0);
}

void    builtin_exec_list(t_list *data, t_shell *shell)
{
    if (ft_strcmp(data->args[0], "echo") == 0)
        ft_echo(data->args);
    else if (ft_strcmp(data->args[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(data->args[0], "env") == 0)
        ft_env(shell->env);
    else if (ft_strcmp(data->args[0], "exit") == 0)
        ft_exit_list(0, shell, data);
    else if (ft_strcmp(data->args[0], "cd") == 0)
        ft_cd_list(shell, data);
    else if (ft_strcmp(data->args[0], "export") == 0)
        ft_export_list(shell, data);
    else if(ft_strcmp(data->args[0], "unset") == 0)
        ft_unset_list(shell, data);
}

void	exec_cmd_list(t_list *data, t_shell *shell)
{
	pid_t	pid;
	char	**env_exec;
	char	*path;
	int		status;

	pid = fork();
	if (pid < 0)
		return;
	else if (pid == 0)
	{
		env_exec = list_to_array(shell->env);
		path = ft_path(data->args[0], env_exec);
		if (path == NULL)
		{
			ft_putstr_fd(data->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(path);
			ft_free(env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			list_clear(&data);
			exit(127);
		}
		if (execve(path, data->args, env_exec) == -1)
		{
			ft_putstr_fd(data->args[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(path);
			ft_free(env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			list_clear(&data);
			exit(127);
		}
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
}

int	exec_list(t_list *data, t_shell *shell)
{
	t_list *curr;

	if (!data)
		return (-1);
	else
	{
		curr = data;
		while (curr != NULL)
		{
			if (is_builtin_list(data) == 1)
				builtin_exec_list(data, shell);
			else
				exec_cmd_list(data, shell);
			curr = curr->next;
		}
		return (0);
	}
	return (-1);
}