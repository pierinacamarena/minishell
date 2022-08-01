/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirec_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/29 20:54:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/01 23:05:53 by pcamaren         ###   ########.fr       */
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
		len = array_size(args);
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
		else if (ft_strcmp(args[len -1], ">") == 0)
		{
			write_error("minishell: syntax error near expected token 'newline'");
			return (1);
		}
		return (0);
	}
	return (-1);
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
	return (-1);
}

int	check_double_redir_left(char **args, t_list *list)
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
		if ((ft_strcmp(args[i], "<<") == 0))
		{
			if (i == 0)
				list->start_redir = 1;
			list->here_doc_left = 1;
			list->redir_qty++;
		}
		i++;
	}
	return (0);
}

int	check_double_redir_right(char **args, t_list *list)
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
		if ((ft_strcmp(args[i], ">>") == 0))
		{
			if (i == 0)
				list->start_redir = 1;
			list->here_doc = 1;
			list->redir_qty++;
		}
		i++;
	}
	return (0);
}

int	check_redir_right(char **args, t_list *list)
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
			list->right_redir = 1;
			list->redir_qty++;
		}
		i++;
	}
	return (0);
}

int	check_redir_left(char **args, t_list *list)
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
		if ((ft_strcmp(args[i], "<") == 0))
		{
			if (i == 0)
				list->start_redir = 1;
			list->left_redir = 1;
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
			if (check_redir_right(curr->args, curr) == -1)
				return (-1);
			curr = curr->next;
		}
		curr = cmds;
		while (curr != NULL)
		{
			if (check_redir_left(curr->args, curr) == -1)
				return (-1);
			curr = curr->next;
		}
		curr = cmds;
		while (curr != NULL)
		{
			if (check_double_redir_right(curr->args, curr) == -1)
				return (-1);
			curr = curr->next;
		}
		curr = cmds;
		while (curr != NULL)
		{
			if (check_double_redir_left(curr->args, curr) == -1)
				return (-1);
			curr = curr->next;
		}
		return (0);
	}
}


//to handle later
	//command > file > file2 >> file3 > file4 >> file5
	//the one that is > will recreate the file
	//the one that is >> will do nothing to the file                            

// command > file
	//if the file exists it will replace whatever content exists with the content generated 
	//by the command
	
// > file 
	//creates the file, if the file already exists it will erase all its content. 

// command > file > file2 > file3 > file4
	//this will create all the files if they dont exist
	//it will add the content to the last file
	//if the previous files had content it will delete the content,this is done with O_trunc

// command >> file
	//will append the result of the command to the end of the file

// command >> file >> file >> file
	//will append to the last file and will leave the other files unchanged

// in between > > there has to be a command, assume it will be properly done by the parsing