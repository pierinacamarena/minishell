/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 19:21:42 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 12:49:59 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_child(t_pipeline *data, t_shell *shell, t_pipex *pipex)
{
	char	*path;

	siginit(SIGINT, SIG_DFL);
	siginit(SIGQUIT, SIG_DFL);
	if (pipex->rw_fds[0] == -1 || pipex->rw_fds[1] == -1)
		free_exit(1, shell, data, ENV | CMD | HIST);
	dup2(pipex->rw_fds[0], 0);
	dup2(pipex->rw_fds[1], 1);
	close_pipes(&pipex->pipes);
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

static int	exec_cmd(t_pipeline *data, t_shell *shell, t_pipex *pipex)
{
	int	built_check;

	built_check = 0;
	if (is_builtin_list(data))
	{	
		pipex->exit = builtin_exec_list(data, shell, pipex->rw_fds);
		if (data->next == NULL)
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

	built_check = 0;
	siginit(SIGINT, SIG_IGN);
	init_pipes(&pipex.pipes, data, shell);
	command_num = 0;
	while (data)
	{
		init_fds(data, &pipex, command_num);
		built_check = exec_cmd(data, shell, &pipex);
		command_num++;
		data = data->next;
	}
	close_pipes(&pipex.pipes);
	pipex.exit = wait_children(pipex.exit, pipex.pid, built_check);
	return (pipex.exit);
}
