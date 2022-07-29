/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/21 17:14:48 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/21 17:14:50 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exec(t_shell *shell)
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
		path = ft_path(shell->cmds[0], env_exec);
		if (path == NULL)
		{
			ft_putstr_fd(shell->cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			// printf("%s: command not found\n", shell->cmds[0]);
			free(path);
			ft_free(env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			exit(127);
		}
		if (execve(path, shell->cmds, env_exec) == -1)
		{
			ft_putstr_fd(shell->cmds[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			// printf("%s: command not found\n", shell->cmds[0]);
			free(path);
			ft_free(env_exec);
			ft_free(shell->cmds);
			ft_free_list(&shell->env);
			ft_free_list(&shell->exp);
			exit(127);
		}
	}
	waitpid(pid, &status, WUNTRACED | WCONTINUED);
}

//create a new process for each command
/*
have an int that tracks the number of pipes that are present


int	end[2]
go over the command linked list
while (list)
{
	//there is a check here i dont understand, if data->cmd[0] == 0
	run the pipe
		(it is a good idea to give to each command node the result of the pid, because i will need it later, so save it in the structure) 
	list = list->next // go to the next node;
}
if there is one or more pipes left 
	close(pipe[0]) close the read end of the pipe 
loop over the list again 
while (list)
{
	waitpid(id of current node, )
	list = list->next;
}


pid_t run_pipe(int *end)
{
	pid_t pid;

	pipe(end);
	pid = fork();

	if (pid < 0)
		exit(1);
	if (pid == 0)
	{
		if (i am not )
	}
	else
	{
		close(end[1]);
	}

}
*/