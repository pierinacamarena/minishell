/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 16:17:40 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 16:27:44 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	match(int type, t_parse *pack)
{
	if (pack->current->type != type && *pack->panic != PANIC_MODE)
	{
		printf("syntax error near unexpected token '%.*s'\n", \
		pack->current->length, pack->current->start);
		*pack->panic = PANIC_MODE;
	}
	*pack->current = scan_token(pack->scanner);
}

static void	command_elem(t_parse *pack, t_elem **elem_list, t_shell *shell)
{
	int		type;

	type = SIMPLE_WORD;
	if (pack->current->type == LESS_TOKEN)
	{
		match(LESS_TOKEN, pack);
		type = READ_FILE;
	}
	else if (pack->current->type == LESS_LESS_TOKEN)
	{
		match(LESS_LESS_TOKEN, pack);
		type = HERE_DOC;
	}
	else if (pack->current->type == MORE_TOKEN)
	{
		match(MORE_TOKEN, pack);
		type = WRITE_FILE;
	}
	else if (pack->current->type == MORE_MORE_TOKEN)
	{
		match(MORE_MORE_TOKEN, pack);
		type = APPEND_FILE;
	}
	*elem_list = new_elem(*elem_list, *pack->current, type, shell);
	match(WORD_TOKEN, pack);
}

static void	command(t_parse *pack, t_elem **elem_list, t_shell *shell)
{
	command_elem(pack, elem_list, shell);
	if (pack->current->type != PIPE_TOKEN \
		&& pack->current->type != OR_TOKEN \
		&& pack->current->type != AND_TOKEN \
		&& pack->current->type != EOF_TOKEN)
		command(pack, elem_list, shell);
}

static t_pipeline	*pipeline(t_pipeline *cmds, t_parse *pack, t_shell *shell)
{
	t_elem	*elem_list;
	t_elem	*words_list;
	t_elem	*tmp;

	if (pack->current->type == EOF_TOKEN)
		return (NULL);
	elem_list = NULL;
	command(pack, &elem_list, shell);
	words_list = NULL;
	while (elem_list != NULL)
	{
		words_list = new_words_list(words_list, elem_list);
		tmp = elem_list;
		elem_list = elem_list->next;
		free_elem(tmp);
	}
	cmds = new_command(cmds, words_list);
	free_elem_list(words_list);
	if (pack->current->type == PIPE_TOKEN)
	{
		match(PIPE_TOKEN, pack);
		cmds->next = pipeline(cmds->next, pack, shell);
	}
	return (cmds);
}

int	parse(t_scanner *scanner, t_shell *shell)
{
	t_pipeline	*cmds;
	t_parse		pack;
	t_token		current;
	int			panic;

	panic = REGULAR_MODE;
	current = scan_token(scanner);
	pack.current = &current;
	pack.scanner = scanner;
	pack.panic = &panic;
	cmds = NULL;
	cmds = pipeline(cmds, &pack, shell);
	if (*cmds->command != NULL && *pack.panic == REGULAR_MODE)
		g_exit_code = exec_pipes(cmds, shell);
	free_commands_list(cmds);
	return (current.type);
}
