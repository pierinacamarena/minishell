/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 12:47:55 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 20:18:52 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_list(t_pipeline *data)
{
	int			count;

	count = 0;
	while (data != NULL)
	{
		count++;
		data = data->next;
	}
	return (count);
}

void	init_pipes(t_pipes *pipes, t_pipeline *data, t_shell *shell)
{
	int	i;

	pipes->size = count_list(data) - 1;
	if (pipes->size <= 0)
		return ;
	pipes->fd_pipe = (int **)malloc(sizeof(int *) * pipes->size);
	if (pipes->fd_pipe == NULL)
		free_exit(-1, shell, data, ENV | CMD | HIST);
	i = 0;
	while (i < pipes->size)
	{
		pipes->fd_pipe[i] = (int *)malloc(sizeof(int) * 2);
		if (pipes->fd_pipe[i] == NULL)
			free_exit(-1, shell, data, ENV | CMD | HIST);
		i++;
	}
	i = 0;
	while (i < pipes->size)
	{
		if (pipe(pipes->fd_pipe[i++]) < 0)
		{
			perror("pipe");
			free_exit(127, shell, data, ENV | CMD | HIST);
		}
	}
}

void	close_pipes(t_pipes *pipes)
{
	int	i;

	i = 0;
	while (i < pipes->size)
	{
		close(pipes->fd_pipe[i][0]);
		close(pipes->fd_pipe[i][1]);
		i++;
	}
}

void	init_fds(t_pipeline *data, t_pipex *pipex, int command_num)
{
	pipex->rw_fds[0] = STDIN_FILENO;
	pipex->rw_fds[1] = STDOUT_FILENO;
	if (command_num > 0)
		pipex->rw_fds[0] = pipex->pipes.fd_pipe[command_num - 1][0];
	if (command_num < pipex->pipes.size)
		pipex->rw_fds[1] = pipex->pipes.fd_pipe[command_num][1];
	get_redirs(data->redirections, pipex->rw_fds);
}

int	wait_children(int exit_status, pid_t pid, int built_check)
{
	int	status;

	status = 0;
	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && built_check == 0)
		exit_status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status) && built_check == 0)
		exit_status = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > 0)
		;
	return (exit_status);
}
