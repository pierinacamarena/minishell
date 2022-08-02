/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/28 17:36:16 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/01 20:13:20 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int exit_fatal(void)
{
	show_error("error: fatal\n");
	exit(EXIT_FAILURE);
	return (EXIT_FAILURE);
}

int show_error(char const *str)
{
	if (str)
		write(STDERR, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

int add_arg(t_list *cmd, char *arg)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = NULL;
	if (!(tmp = (char**)malloc(sizeof(*tmp) * (cmd->length + 2))))
		return (exit_fatal());
	while (i < cmd->length)
	{
		tmp[i] = cmd->args[i];
		i++;
	}
	if (cmd->length > 0)
		free(cmd->args);
	cmd->args = tmp;
	cmd->args[i++] = ft_strdup(arg);
	cmd->args[i] = 0;
	cmd->length++;
	return (EXIT_SUCCESS);
}

int list_rewind(t_list **list)
{
	while (*list && (*list)->previous)
		*list = (*list)->previous;
	return (EXIT_SUCCESS);
}

int list_clear(t_list **cmds)
{
	t_list	*tmp;
	int		i;

	list_rewind(cmds);
	while (*cmds)
	{
		tmp = (*cmds)->next;
		i = 0;
		while (i < (*cmds)->length)
			free((*cmds)->args[i++]);
		free((*cmds)->args);
		free(*cmds);
		*cmds = tmp;
	}
	*cmds = NULL;
	return (EXIT_SUCCESS);
}

int list_push(t_list **list, char *arg)
{
	t_list	*new;

	if (!(new = (t_list*)malloc(sizeof(*new))))
		return (exit_fatal());
	new->args = NULL;
	new->length = 0;
	new->type = TYPE_END;
	new->right_redir = 0;
	new->start_redir = 0;
	new->here_doc = 0;
	new->here_doc_left = 0;
	new->left_redir = 0;
	new->redir_qty = 0;
	new->previous = NULL;
	new->next = NULL;
	if (*list)
	{
		(*list)->next = new;
		new->previous = *list;
	}
	*list = new;
	return (add_arg(new, arg));
}

int parse_arg(t_list **cmds, char *arg)
{
	int	punto_coma;

	punto_coma = (strcmp(";", arg) == 0);
	if (punto_coma && !*cmds)
		return (EXIT_SUCCESS);
	else if (!punto_coma && (!*cmds || (*cmds)->type > TYPE_END))
	{
		return (list_push(cmds, arg));
	}
	else if (strcmp("|", arg) == 0)
	{
		(*cmds)->type = TYPE_PIPE;
	}
	else if (punto_coma)
	{
		(*cmds)->type = TYPE_BREAK;
	}
	else
	{
		return (add_arg(*cmds, arg));
	}
	return (EXIT_SUCCESS);
}

void	print_parse_list(t_list *cmds)
{
	t_list	*curr;
	int		i;

	i = 1;
	if (!cmds)
		return;
	else
	{
	curr = cmds;
	while (curr != NULL)
	{
		printf("node %d\n", i);
		printf("type is: %d\n", curr->type);
		printf("start_redir is: %d\n", curr->start_redir);
		printf("redir quantity is: %d\n", curr->redir_qty);
		printf("right_redir: %d\n", curr->right_redir);
		printf("left_redir: %d\n", curr->left_redir);
		printf("here_doc: %d\n", curr->here_doc);
		printf("here_doc_left: %d\n", curr->here_doc_left);
		i++;
		curr = curr->next;
	}
	}
}
