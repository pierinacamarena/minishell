#include "../includes/minishell.h"

static void	match(int type, t_pack *pack)
{ 
	if (pack->current->type != type && *pack->panic != PANIC_MODE)
	{
		printf("syntax error near unexpected token '%.*s'\n", \
		current->length, current->start);
		*pack->panic = PANIC_MODE;
	}
	*pack->current = scan_token(scanner);
}

static void	command_elem(t_pack *pack, t_elem **elem_list, t_shell *shell)
{
	int		type;

	type = SIMPLE_WORD;
	if (pack->current->type == LESS_TOKEN)
	{
		match(LESS_TOKEN, pack);
		type = READ_FILE;
	}
	else if (current->type == LESS_LESS_TOKEN)
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

static void	command(t_pack *pack, t_elem **elem_list, t_shell *shell)
{
	command_elem(pack, elem_list, shell);
	if (pack->current->type != PIPE_TOKEN \
		&& pack->current->type != OR_TOKEN \
		&& pack->current->type != AND_TOKEN \
		&& pack->current->type != EOF_TOKEN)
		command(pack, elem_list, shell);
}

static t_pipeline	*pipeline(t_pipeline *commands_list, t_pack *pack, t_shell *shell)
{
	t_elem	*elem_list;
	t_elem	*words_list;
	t_elem	*tmp;

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
	commands_list = new_command(commands_list, words_list);
	free_elem_list(words_list);
	if (pack->current->type == PIPE_TOKEN)
	{
		match(PIPE_TOKEN, pack);
		commands_list->next = pipeline(commands_list->next, pack, shell);
	}
	return (commands_list);
}

static void	list(t_parse *pack, t_shell *shell)
{
	t_pipeline	*commands_list;

	if (pack->current->type == EOF_TOKEN)
		return ;
	commands_list = NULL;
	commands_list = pipeline(commands_list, pack, shell);
	if (*panic == REGULAR_MODE)
		exec_pipes(commands_list, shell);
	free_commands_list(commands_list);
	if (pack->current->type == OR_TOKEN)
	{
		match(OR_TOKEN, pack);
		list(pack, shell);
	}
	else if (pack->current->type == AND_TOKEN)
	{
		match(AND_TOKEN, pack);
		list(pack, shell);
	}
}

int	parse(t_scanner *scanner, t_shell *shell)
{
	t_parse		pack;
	t_token		current;
	int			panic;

	panic = REGULAR_MODE;
	current = scan_token(scanner);
	pack.current = &current;
	pack.scanner = scanner;
	pack.panic = &panic;
	list(&pack, shell);
	return (current.type);
}
