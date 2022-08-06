/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:25:32 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 21:04:51 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin_list(t_pipeline *data)
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
	else if (ft_strcmp(data->command[0], "unset") == 0)
		return (1);
	return (0);
}

int	builtin_exec_list(t_pipeline *data, t_shell *shell, int *rw_fds)
{
	int	exit_status;

	exit_status = 0;
	if (ft_strcmp(data->command[0], "echo") == 0)
		exit_status = ft_echo(data->command, rw_fds);
	else if (ft_strcmp(data->command[0], "pwd") == 0)
		exit_status = ft_pwd(rw_fds);
	else if (ft_strcmp(data->command[0], "env") == 0)
		exit_status = ft_env(shell->env, rw_fds);
	else if (ft_strcmp(data->command[0], "exit") == 0)
		exit_status = ft_exit_list(shell, data);
	else if (ft_strcmp(data->command[0], "cd") == 0)
		exit_status = ft_cd_list(shell, data);
	else if (ft_strcmp(data->command[0], "export") == 0)
		exit_status = ft_export_list(shell, data, rw_fds);
	else if (ft_strcmp(data->command[0], "unset") == 0)
		exit_status = ft_unset_list(shell, data);
	else
		exit_status = 0;
	return (exit_status);
}

int	get_heredoc(char *heredoc)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	line = readline("> ");
	while (line != NULL && ft_strcmp(heredoc, line) != 0)
	{
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		line = readline("> ");
	}
	free(line);
	close(pipefd[1]);
	return (pipefd[0]);
}

int	do_redir(t_elem *redirections)
{
	int	fd;

	if (redirections == NULL)
		return (-1);
	if (redirections->type == WRITE_FILE)
		fd = open(redirections->words, O_TRUNC | O_CREAT | O_WRONLY, 00644);
	else if (redirections->type == READ_FILE)
		fd = open(redirections->words, O_RDONLY);
	else if (redirections->type == APPEND_FILE)
		fd = open(redirections->words, O_APPEND | O_CREAT | O_WRONLY, 00644);
	else
		fd = get_heredoc(redirections->words);
	if (fd == -1)
		perror(redirections->words);
	return (fd);
}

void	get_redirs(t_elem *redirs, int *rw_fds)
{
	while (redirs != NULL)
	{
		if (redirs->type == APPEND_FILE || redirs->type == WRITE_FILE)
		{
			if (rw_fds[1] != STDOUT_FILENO)
				close(rw_fds[1]);
			rw_fds[1] = do_redir(redirs);
		}
		else
		{
			if (rw_fds[0] != STDIN_FILENO)
				close(rw_fds[0]);
			rw_fds[0] = do_redir(redirs);
		}
		if (rw_fds[0] == -1 || rw_fds[1] == -1)
			break ;
		redirs = redirs->next;
	}
}
