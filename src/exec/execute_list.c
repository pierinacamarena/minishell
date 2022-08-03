/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:25:32 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/03 14:24:37 by pcamaren         ###   ########.fr       */
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

int	get_heredoc(char *heredoc)
{
	int		pipefd[2];
	char	*line;

	pipe(pipefd);
	line = readline("> ");
	while (line != NULL && strcmp(heredoc, line) != 0) //add ft_strcmp
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
		fd = open(redirections->words, O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else if (redirections->type == READ_FILE)
		fd = open(redirections->words, O_RDONLY);
	else if (redirections->type == APPEND_FILE)
		fd = open(redirections->words, O_APPEND | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	else
		fd = get_heredoc(redirections->words);
	return (fd);
}

void	get_redirs(t_elem *redirections, int *read_write_fds)
{
	while (redirections != NULL)
	{
		if (redirections->type == APPEND_FILE || redirections->type == WRITE_FILE)
		{
			if (read_write_fds[1] != STDOUT_FILENO)
				close(read_write_fds[1]);
			read_write_fds[1] = do_redir(redirections);
		}
		else
		{
			if (read_write_fds[0] != STDIN_FILENO)
				close(read_write_fds[0]);
			read_write_fds[0] = do_redir(redirections);
		}
		redirections=redirections->next;
	}
}

int	exec_pipes(t_pipeline *data, t_shell *shell)
{
	t_pipes		pipes;
	int			i;
	pid_t		pid;
	int			command_num;
	int			status;
	int			exit_status;
	int			read_write_fds[2];

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
			perror("pipe");
			ft_exit_list(127, shell, data);
		}
		i++;
	}
	command_num = 0;
	while (data)
	{
		if (is_builtin_list(data) == 1)
			builtin_exec_list(data, shell);
		else
		{
			pid = fork();
			if (pid == 0)
			{
				read_write_fds[0] = STDIN_FILENO;
				read_write_fds[1] = STDOUT_FILENO;
				//if NOT first command
				if (command_num > 0)
				{
					read_write_fds[0] = pipes.fd_pipe[command_num - 1][0];
					// if (dup2(pipes.fd_pipe[command_num - 1][0], 0) < 0)
					// {
					// 	perror("dup");
					// 	ft_exit_list(127, shell, data);
					// }
				}
				//if NOT last command
				if (command_num < pipes.size)
				{
					read_write_fds[1] = pipes.fd_pipe[command_num][1];
					// if (dup2(pipes.fd_pipe[command_num][1], 1) < 0)
					// {
					// 	perror("dup2");
					// 	ft_exit_list(127, shell, data);
					// }
				}
				get_redirs(data->redirections, read_write_fds);
				dup2(read_write_fds[0], 0);
				dup2(read_write_fds[1], 1);
				i = 0;
				while (i < pipes.size)
				{
					close(pipes.fd_pipe[i][0]);
					close(pipes.fd_pipe[i][1]);
					i++;
				}
			exec(data, shell);
			}
		}
		command_num++;
		data = data->next;
	}
	i = 0;
	while (i < pipes.size)
	{
		close(pipes.fd_pipe[i][0]);
		close(pipes.fd_pipe[i][1]);
		i++;
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		exit_status = WEXITSTATUS(status);
	while (waitpid(-1, &status, 0) > 0)
		;
	return (exit_status);
}