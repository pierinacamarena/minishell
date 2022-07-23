#include "parser.h"

static void	match(int type, t_token *current, t_scanner *scanner)
{
	if (current->type != type)
	{
		//add panic mode
		fprintf(stderr, "syntax error near unexpected token '%.*s'\n",
		current->length, current->start);
		exit(EXIT_FAILURE);
	}
	*current = scan_token(scanner);
}

static void	command_elem(t_token *current, t_scanner *scanner, t_elem **elem_list)
{
	int		type;

	type = SIMPLE_WORD;
	if (current->type == LESS_TOKEN)
	{
		match(LESS_TOKEN, current, scanner);
		type = READ_FILE;
	}
	else if (current->type == LESS_LESS_TOKEN)
	{
		match(LESS_LESS_TOKEN, current, scanner);
		type = HERE_DOC;
	}
	else if (current->type == MORE_TOKEN)
	{
		match(MORE_TOKEN, current, scanner);
		type = WRITE_FILE;
	}
	else if (current->type == MORE_MORE_TOKEN)
	{
		match(MORE_MORE_TOKEN, current, scanner);
		type = APPEND_FILE;
	}
	*elem_list = new_elem(*elem_list, *current, type);
	match(WORD_TOKEN, current, scanner);
}

static void	command(t_token *current, t_scanner *scanner, t_elem **elem_list)
{
	command_elem(current, scanner, elem_list);
	if (current->type != PIPE_TOKEN \
		&& current->type != OR_TOKEN \
		&& current->type != AND_TOKEN \
		&& current->type != EOF_TOKEN)
		command(current, scanner, elem_list);
}

static t_pipeline	*pipeline(t_pipeline *commands_list, t_token *current, t_scanner *scanner)
{
	t_elem	*elem_list;
	t_elem	*words_list;
	t_elem	*tmp;

	elem_list = NULL;
	command(current, scanner, &elem_list);
	words_list = NULL;
	while (elem_list != NULL)
	{
		words_list = new_words_list(words_list, elem_list);
		tmp = elem_list;
		elem_list = elem_list->next;
		free_elem(tmp);
	}
	commands_list = new_command(commands_list, words_list);
	if (current->type == PIPE_TOKEN)
	{
		match(PIPE_TOKEN, current, scanner);
		commands_list->next = pipeline(commands_list->next, current, scanner);
	}
	return (commands_list);
}

static void	list(t_token *current, t_scanner *scanner)
{
	t_pipeline	*commands_list;

	if (current->type == EOF_TOKEN)
		return ;
	commands_list = NULL;
	commands_list = pipeline(commands_list, current, scanner);
	print_commands_list(commands_list);
	if (current->type == OR_TOKEN)
	{
		match(OR_TOKEN, current, scanner);
		list(current, scanner);
	}
	else if (current->type == AND_TOKEN)
	{
		match(AND_TOKEN, current, scanner);
		list(current, scanner);
	}
}

int	parse(t_scanner *scanner)
{
	t_token		current;

	current = scan_token(scanner);
	list(&current, scanner);
	return (current.type);
}
