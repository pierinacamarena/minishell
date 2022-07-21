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
	t_token	previous;
	int		type;

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
	else
		type = SIMPLE_WORD;
	previous = *current;
	match(WORD_TOKEN, current, scanner);
	*elem_list = new_elem(*elem_list, previous, type);
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

static void	pipeline(t_token *current, t_scanner *scanner)
{
	t_elem	*elem_list;

	elem_list = NULL;
	command(current, scanner, &elem_list);
	print_elem_list(elem_list);	
	if (current->type == PIPE_TOKEN)
	{
		match(PIPE_TOKEN, current, scanner);
		pipeline(current, scanner);
	}
}

static void	list(t_token *current, t_scanner *scanner)
{
	if (current->type == EOF_TOKEN)
		return ;
	pipeline(current, scanner);
	if (current->type == OR_TOKEN)
	{
		match(OR_TOKEN, current, scanner);
		pipeline(current, scanner);
	}
	else if (current->type == AND_TOKEN)
	{
		match(AND_TOKEN, current, scanner);
		pipeline(current, scanner);
	}
}

int	parse(t_scanner *scanner)
{
	t_token		current;

	current = scan_token(scanner);
	list(&current, scanner);
	return (current.type);
}
