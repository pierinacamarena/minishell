/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 20:54:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/29 23:20:25 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/minishell.h"

int	continuous_redir(char *arg)
{
	if (arg[0] == '>' && arg[1] == '>' && arg[2] == '>')
		return (1);
	return (0);
}

int	continuous_redir_left(char *arg)
{
	if (arg[0] == '<' && arg[1] == '<' && arg[2] == '<')
		return (1);
	return (0);
}
int	check_redir_error_right(char **args)
{
	int	len;

	if (args[0] == NULL)
		return (-1);
	if (args[1])
	{
		if ((ft_strcmp(args[0], ">") == 0) && (ft_strcmp(args[1], ">") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], ">") == 0) && args[1] == NULL)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], ">>") == 0) && (ft_strcmp(args[1], ">>") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], ">>") == 0) && args[1] == NULL)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		if ((ft_strcmp(args[0], ">") == 0) && (ft_strcmp(args[1], ">>") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], ">>") == 0) && (ft_strcmp(args[1], ">") == 0))
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if (continuous_redir_left(args[0]) == 1)
		{
			write_error("minishell: syntax error near expected token '>>'");
			return (1);
		}
		len = array_size(args);
		else if (ft_strcmp(args[len -1], ">") == 0)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		return (0);
	}
}

int	check_redir_error_left(char **args)
{
	if (args[0] == NULL)
		return (-1);
	if (args[1])
	{
		if ((ft_strcmp(args[0], "<") == 0) && (ft_strcmp(args[1], "<") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], "<") == 0) && args[1] == NULL)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], "<<") == 0) && (ft_strcmp(args[1], "<<") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], "<<") == 0) && args[1] == NULL)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		if ((ft_strcmp(args[0], "<") == 0) && (ft_strcmp(args[1], "<<") == 0))
		{	
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if ((ft_strcmp(args[0], "<<") == 0) && (ft_strcmp(args[1], "<") == 0))
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		else if (continuous_redir(args[0]) == 1)
		{
			write_error("minishell: syntax error near expected token '>>'");
			return (1);
		}
		return (0);
	}
}

int	check_redir_start(char **args, t_list *list)
{
	int	i;

	i = 0;
	if (args[0] == NULL)
		return (-1);
	if (check_redir_error_right(args) == 1)
		return (-1);
	else if (check_redir_error_left(args) == 1)
		return (-1);
	while (args[i])
	{
		if ((ft_strcmp(args[i], ">") == 0))
		{
			if (i == 0)
				list->start_redir = 1;
			list->has_redir = 1;
			list->redir_qty++;
		}
		i++;
	}
	return (0);
}


int	set_redir(t_list *cmds)
{
	t_list *curr;

	if (cmds == NULL)
		return (-1);
	else
	{
		curr = cmds;
		while (curr != NULL)
		{
			if (check_redir_start(curr) == -1)
				return (-1);
			curr = curr->next;
		}
	}
}