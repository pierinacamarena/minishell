/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:25:32 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/03 00:01:20 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int     is_builtin_list(t_pipeline *data)
{
    if (ft_strcmp(data->command[0], "echo") == 0)
        return (1);
    else if (ft_strcmp(data->command[0], "pwd") == 0)
        return (1);
    else if (ft_strcmp(data->command[0], "env") == 0)
        return (1);
    else if (ft_strcmp(data->command[0], "exit") == 0)
        return (1);
    else if (ft_strcmp(data->command[0], "cd") == 0)
        return (1);
    else if (ft_strcmp(data->command[0], "export") == 0)
        return (1);
    else if(ft_strcmp(data->command[0], "unset") == 0)
        return (1);
    return (0);
}

void    builtin_exec_list(t_pipeline *data, t_shell *shell)
{
    if (ft_strcmp(data->command[0], "echo") == 0)
        ft_echo(data->command);
    else if (ft_strcmp(data->command[0], "pwd") == 0)
        ft_pwd();
    else if (ft_strcmp(data->command[0], "env") == 0)
        ft_env(shell->env);
    else if (ft_strcmp(data->command[0], "exit") == 0)
        ft_exit_list(0, shell, data);
    else if (ft_strcmp(data->command[0], "cd") == 0)
        ft_cd_list(shell, data);
    else if (ft_strcmp(data->command[0], "export") == 0)
        ft_export_list(shell, data);
    else if(ft_strcmp(data->command[0], "unset") == 0)
        ft_unset_list(shell, data);
}

int	count_list(t_pipeline *data)
{
	t_pipeline	*curr;
	int			count;

	count = 0;
	if (!data)
		return (-1);
	else
	{
		curr = data;
		while (curr != NULL)
		{
			count++;
			curr = curr->next;
		}
		return (count);
	}
}

int	exec_pipes(t_pipeline *data, t_shell *shell)
{
	t_pipes		pipes;
	t_pipeline	*cur;
	int			i;
	pid_t		pid;
	int			command_num;

	i = 0;
	pipes.size = count_list(data) - 1;
	pipes.fd_pipe = (int **)malloc(sizeof(int) * pipes.size);
	if (!pipes.fd_pipe)
		return (-1);
	while (i < pipes.size)
	{
		pipes.fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (!pipes.fd_pipe[i])
			return (-1);
		i++;
	}
	i = 0;
	while (i < pipes.size)
	{
		if (pipe(pipes.fd_pipe[i]) < 0)
		{
			write_error("fatal error with pipes");
			ft_exit_list(127, shell, data);
		}
	}
	command_num = 0;
	while (data)
	{
		pid = fork();
		if (pid == 0)
		{
			if (command > 0)
			{
				if (dup2(pipes.fd_pipe[command - 1], 0) < 0)
				{
					write_error("fatal error with dup");
					ft_exit_list(127, shell, data);
				}
        	}
			if (command < pipes.size)
			{
				if (dup2(pipes.fd_pipe[command], 1) < 0)
				{
					write_error("fatal error with dup");
					ft_exit_list(127, shell, data);
				}
			}
			//close all pipes
			i = 0;
			while (i < pipes.size)
			{
				close(pipes.fd_pipe[i]);
				i++;
			}	
		}
		else
		{
			waitpid(pid, &status, WUNTRACED | WCONTINUED);
			i = 0;
			while (i < pipes.size)
			{
				close(pipes.fd_pipe[i]);
				i++;
			}	
		}
		command_num++;
}
}

void	exec(t_pipeline *data, t_shell *shell)
{
	char	*path;
	
	shell->env_exec = list_to_array(shell->env);
	path = ft_path(data->command[0], shell->env_exec);
	if (path == NULL)
	{
		ft_putstr_fd(data->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		ft_free(shell->env_exec);
		ft_free_list(&shell->env);
		ft_free_list(&shell->exp);
		free_commands_list(data);
		exit(127);
	}
	if (execve(path, data->command, shell->env_exec) == -1)
	{
		ft_putstr_fd(data->command[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free(path);
		ft_free(shell->env_exec);
		ft_free_list(&shell->env);
		ft_free_list(&shell->exp);
		free_commands_list(data);
		exit(127);
	}
}

int	exec_cmd_list(t_pipeline *data, t_shell *shell)
{
	pid_t	pid;
	int		status;
	int		ret;

	ret = EXIT_FAILURE;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		exec(data, shell);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		// if (WIFEXITED(status))
		// 	ret = WEXITSTATUS(status);
	}
	return (ret);
}

int	exec_list(t_pipeline *data, t_shell *shell)
{
	t_pipeline	*curr;
	int		ret;

	ret = EXIT_SUCCESS;
	if (!data)
		return (-1);
	else
	{
		while (data != NULL)
		{
			curr = data;
			if (is_builtin_list(curr) == 1)
				builtin_exec_list(curr, shell);
			else
				exec_cmd_list(curr, shell);
			if (!(data)->next)
				break ;
			data = data->next;
		}
		return (ret);
	}
}