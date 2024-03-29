/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:42 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/07 14:23:26 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->size)
		free(pipes->fd_pipe[i++]);
	if (i != 0)
		free(pipes->fd_pipe);
}

static int	exec(char *path, t_pipeline *data, t_shell *shell)
{
	int	exit_status;

	if (path == NULL && g_exit_code == 126)
	{
		write_error(data->command[0]);
		write_error(": permission denied\n");
		exit_status = 126;
	}
	else if (path == NULL)
	{
		write_error(data->command[0]);
		write_error(": command not found\n");
		exit_status = 127;
	}
	else
	{
		execve(path, data->command, shell->env_exec);
		perror(data->command[0]);
		exit_status = 127;
	}
	return (exit_status);
}

static void	exec_child(t_pipeline *data, t_shell *shell, t_pipex *pipex)
{
	char	*path;
	int		exit_status;

	siginit(SIGINT, SIG_DFL);
	siginit(SIGQUIT, SIG_DFL);
	if (pipex->rw_fds[0] == -1 || pipex->rw_fds[1] == -1)
		free_exit(1, shell, data, ENV | CMD | HIST);
	dup2(pipex->rw_fds[0], 0);
	dup2(pipex->rw_fds[1], 1);
	close_pipes(&pipex->pipes);
	free_pipes(&pipex->pipes);
	shell->env_exec = list_to_array(shell->env);
	path = ft_path(data->command[0], shell->env_exec);
	exit_status = exec(path, data, shell);
	free(path);
	ft_free(shell->env_exec);
	free_exit(exit_status, shell, data, ENV | CMD | HIST);
}

static int	exec_cmd(t_pipeline *data, t_shell *shell, t_pipex *pipex)
{
	int	built_check;

	built_check = 0;
	if (is_builtin_list(data))
	{	
		pipex->exit = builtin_exec_list(data, shell, pipex->rw_fds);
		built_check = 1;
	}
	else
	{
		pipex->pid = fork();
		if (pipex->pid == 0)
			exec_child(data, shell, pipex);
	}
	return (built_check);
}

int	exec_pipes(t_pipeline *data, t_shell *shell)
{
	t_pipex		pipex;
	int			command_num;
	int			built_check;

	pipex.pid = -1;
	built_check = 0;
	siginit(SIGINT, SIG_IGN);
	init_pipes(&pipex.pipes, data, shell);
	command_num = 0;
	while (data)
	{
		init_fds(data, &pipex, command_num);
		if (data->command[0] != NULL)
			built_check = exec_cmd(data, shell, &pipex);
		command_num++;
		data = data->next;
	}
	close_pipes(&pipex.pipes);
	free_pipes(&pipex.pipes);
	pipex.exit = wait_children(pipex.exit, pipex.pid, built_check);
	return (pipex.exit);
}
