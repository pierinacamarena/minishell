#include "scanner.h"
#include "parser.h"

char	*val_stack[1000];
char	**pos = val_stack;

void	push(const char *lexeme, int len)
{
	if (pos - val_stack < 1000)
		*pos++ = strndup(lexeme, len);
}

char	*pop(void)
{
	if (pos >= val_stack)
		return (*--pos);
}

static void	match(int type, t_token *current, t_scanner *scanner)
{
	if (current->type != type)
	{
		fprintf(stderr, "syntax error near unexpected token '%.*s'\n",
		current->length, current->start);
		exit(EXIT_FAILURE);
	}
	push(current->start, current->length);
	*current = scan_token(scanner);
}

static void	command_elem(t_token *current, t_scanner *scanner)
{
	if (current->type == LESS_TOKEN)
		match(LESS_TOKEN, current, scanner);
	else if (current->type == LESS_LESS_TOKEN)
		match(LESS_LESS_TOKEN, current, scanner);
	else if (current->type == MORE_TOKEN)
		match(MORE_TOKEN, current, scanner);
	else if (current->type == MORE_MORE_TOKEN)
		match(MORE_MORE_TOKEN, current, scanner);
	match(WORD_TOKEN, current, scanner);
}

static void	command(t_token *current, t_scanner *scanner)
{
	char	*lexeme;

	command_elem(current, scanner);
	lexeme = pop();
	printf("%s ", lexeme);
	free(lexeme);
	if (current->type != PIPE_TOKEN \
		&& current->type != OR_TOKEN \
		&& current->type != AND_TOKEN \
		&& current->type != EOF_TOKEN)
		command(current, scanner);
}

static void	pipeline(t_token *current, t_scanner *scanner)
{
	command(current, scanner);
	printf("\n");
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
	t_token	current;

	current = scan_token(scanner);
	list(&current, scanner);
	return (current.type);
}
