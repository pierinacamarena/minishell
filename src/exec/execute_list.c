/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:25:32 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 18:53:06 by pcamaren         ###   ########.fr       */
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
	int			i;

	i = 0;
	pipes.size = count_list(data) - 1;
	pipes.fd_pipe = (int **)malloc(sizeof(int) * pipes.size * 2);
	while (i < pipes.size)
	{
		
	}
}

int	exec_cmd_list(t_pipeline *data, t_shell *shell)
{
	pid_t	pid;
	char	*path;
	int		status;
	int		ret;
	// int		pipe_open;

	ret = EXIT_FAILURE;
	// pipe_open = 0;
	// if (data->type == TYPE_PIPE || (data->previous && data->previous->type == TYPE_PIPE))
	// {
	// 	pipe_open = 1;
	// 	if (pipe(data->pipes))
	// 		return (-1);
	// }
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		// if (data->type == TYPE_PIPE && dup2(data->pipes[1], STDOUT) < 0)
		// 	return (-1);
		// if (data->previous && data->previous->type == TYPE_PIPE && dup2(data->previous->pipes[0], STDIN) < 0)
		// 	return (-1);
		shell->env_exec = list_to_array(shell->env);
		path = ft_path(data->command[0], shell->env_exec);
		if (path == NULL)
		{
			ft_putstr_fd(data->command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(path);
			ft_free(shell->env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			free_commands_list(data);
			// list_clear(&data);
			// clear list function from parse
			exit(127);
		}
		if (execve(path, data->command, shell->env_exec) == -1)
		{
			ft_putstr_fd(data->command[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			free(path);
			ft_free(shell->env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			free_commands_list(data);
			// list_clear(&data);
			// clear list function from parse
			exit(127);
		}
	}
	else
	{
		waitpid(pid, &status, WUNTRACED | WCONTINUED);
		// if (pipe_open)
		// 	close(data->pipes[1]);
		// if (data->previous && data->previous->type == TYPE_PIPE)
		// 	close(data->previous->pipes[0]);
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