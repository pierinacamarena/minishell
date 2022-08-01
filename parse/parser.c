#include "parser.h"
static void	match(int type, t_token *current, t_scanner *scanner, int *panic) { if (current->type != type && *panic != PANIC_MODE)
	{
		printf("syntax error near unexpected token '%.*s'\n", \
		current->length, current->start);
		*panic = PANIC_MODE;
	}
	*current = scan_token(scanner);
}

static void	command_elem(t_token *current, t_scanner *scanner, t_elem **elem_list, int *panic)
{
	int		type;

	type = SIMPLE_WORD;
	if (current->type == LESS_TOKEN)
	{
		match(LESS_TOKEN, current, scanner, panic);
		type = READ_FILE;
	}
	else if (current->type == LESS_LESS_TOKEN)
	{
		match(LESS_LESS_TOKEN, current, scanner, panic);
		type = HERE_DOC;
	}
	else if (current->type == MORE_TOKEN)
	{
		match(MORE_TOKEN, current, scanner, panic);
		type = WRITE_FILE;
	}
	else if (current->type == MORE_MORE_TOKEN)
	{
		match(MORE_MORE_TOKEN, current, scanner, panic);
		type = APPEND_FILE;
	}
	*elem_list = new_elem(*elem_list, *current, type);
	match(WORD_TOKEN, current, scanner, panic);
}

static void	command(t_token *current, t_scanner *scanner, t_elem **elem_list, int *panic)
{
	command_elem(current, scanner, elem_list, panic);
	if (current->type != PIPE_TOKEN \
		&& current->type != OR_TOKEN \
		&& current->type != AND_TOKEN \
		&& current->type != EOF_TOKEN)
		command(current, scanner, elem_list, panic);
}

static t_pipeline	*pipeline(t_pipeline *commands_list, t_token *current, t_scanner *scanner, int *panic)
{
	t_elem	*elem_list;
	t_elem	*words_list;
	t_elem	*tmp;

	elem_list = NULL;
	command(current, scanner, &elem_list, panic);
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
	if (current->type == PIPE_TOKEN)
	{
		match(PIPE_TOKEN, current, scanner, panic);
		commands_list->next = pipeline(commands_list->next, current, scanner, panic);
	}
	return (commands_list);
}

static void	list(t_token *current, t_scanner *scanner, int *panic)
{
	t_pipeline	*commands_list;

	if (current->type == EOF_TOKEN)
		return ;
	commands_list = NULL;
	commands_list = pipeline(commands_list, current, scanner, panic);
	print_commands_list(commands_list);
	free_commands_list(commands_list);
	if (current->type == OR_TOKEN)
	{
		match(OR_TOKEN, current, scanner, panic);
		list(current, scanner, panic);
	}
	else if (current->type == AND_TOKEN)
	{
		match(AND_TOKEN, current, scanner, panic);
		list(current, scanner, panic);
	}
}

int	parse(t_scanner *scanner)
{
	t_token		current;
	int			panic;

	panic = REGULAR_MODE;
	current = scan_token(scanner);
	list(&current, scanner, &panic);
	if (panic == PANIC_MODE)
		return (panic);
	return (current.type);
}
