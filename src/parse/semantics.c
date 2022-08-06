/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantics.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:59:11 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 13:31:34 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmds(t_elem *words_list)
{
	int	i;

	i = 0;
	while (words_list != NULL)
	{
		if (words_list->type == SIMPLE_WORD)
			i++;
		words_list = words_list->next;
	}
	return (i);
}

static char	**get_command(t_elem *words_list)
{
	char	**command;
	char	*command_part;
	int		i;

	i = count_cmds(words_list);
	command = (char **)malloc(sizeof(char *) * (i + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (words_list != NULL)
	{
		if (words_list->type == SIMPLE_WORD)
		{
			command_part = ft_strdup(words_list->words);
			if (command_part == NULL)
				free_exit(-1, NULL, NULL, HIST);
			command[i++] = command_part;
		}
		words_list = words_list->next;
	}
	command[i] = NULL;
	return (command);
}

static t_elem	*get_redirections(t_elem *words_list)
{
	t_elem	*head;
	t_elem	*new_elem;

	head = NULL;
	while (words_list != NULL)
	{
		if (words_list->type != SIMPLE_WORD)
		{
			new_elem = copy_elem(words_list);
			if (new_elem == NULL)
				free_exit(-1, NULL, NULL, HIST);
			head = add_elem_to_list(head, new_elem);
		}
		words_list = words_list->next;
	}
	return (head);
}

t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list)
{
	if (commands_list == NULL)
	{
		commands_list = (t_pipeline *)malloc(sizeof(t_pipeline));
		if (commands_list == NULL)
			free_exit(-1, NULL, commands_list, HIST | CMD);
		commands_list->command = get_command(words_list);
		commands_list->redirections = get_redirections(words_list);
		commands_list->next = NULL;
	}
	else
		commands_list->next = new_command(commands_list->next, words_list);
	return (commands_list);
}
