/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:42 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 21:59:22 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_list(t_pipeline *data)
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
		if (pipe(pipes->fd_pipe[i]) < 0)
		{
			perror("pipe");
			free_exit(127, shell, data, ENV | CMD | HIST);
		}
		i++;
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

static void	exec_child(t_pipeline *data, t_shell *shell, t_pipes *pipes, int *rw)
{
	char	*path;

	siginit(SIGINT, SIG_DFL);
	siginit(SIGQUIT, SIG_DFL);
	if (rw[0] == -1 || rw[1] == -1)
		free_exit(1, shell, data, ENV | CMD | HIST);
	dup2(rw[0], 0);
	dup2(rw[1], 1);
	close_pipes(pipes);
	shell->env_exec = list_to_array(shell->env);
	path = ft_path(data->command[0], shell->env_exec);
	if (path == NULL)
	{
		write_error(data->command[0]);
		write_error(": command not found\n");
	}
	else
	{
		execve(path, data->command, shell->env_exec);
		perror(data->command[0]);
	}
	free(path);
	free_exit(127, shell, data, ENV | CMD | HIST);
}

static void	init_fds(t_pipeline *data, t_pipes pipes, int *rw, int command_num)
{
	rw[0] = STDIN_FILENO;
	rw[1] = STDOUT_FILENO;
	if (command_num > 0)
		rw[0] = pipes.fd_pipe[command_num - 1][0];
	if (command_num < pipes.size)
		rw[1] = pipes.fd_pipe[command_num][1];
	get_redirs(data->redirections, rw);
}

static int	wait_children(int exit_status, pid_t pid, int built_check)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) && built_check == 0)
		exit_status = 128 + WTERMSIG(status);
	else if (WIFEXITED(status) && built_check == 0)
		exit_status = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > 0)
		;
	return (exit_status);
}
	
int	exec_pipes(t_pipeline *data, t_shell *shell)
{
	t_pipes		pipes;
	pid_t		pid;
	int			command_num;
	int			exit_status;
	int			read_write_fds[2];
	int			built_check;

	built_check = 0;
	siginit(SIGINT, SIG_IGN);
	init_pipes(&pipes, data, shell);
	command_num = 0;
	while (data)
	{
		init_fds(data, pipes, read_write_fds, command_num);
		if (is_builtin_list(data))
		{	
			exit_status = builtin_exec_list(data, shell, read_write_fds);
			if (data->next == NULL)
				built_check = 1;
		}
		else
		{
			pid = fork();
			if (pid == 0)
				exec_child(data, shell, &pipes, read_write_fds); 
		}
		command_num++;
		data = data->next;
	}
	close_pipes(&pipes);
	exit_status = wait_children(exit_status, pid, built_check);
	return (exit_status);
}
