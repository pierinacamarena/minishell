#include "scanner.h"

static int	is_meta(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

void	skip_blanks(t_scanner *scanner)
{
	while (*scanner->current != '\0' && isblank(*scanner->current))
		scanner->current++;
}

int	advance(t_scanner *scanner)
{
	int	c;

	c = *scanner->current;
	scanner->current++;
	return (c);
}

void	init_scanner(t_scanner *scanner, const char *line)
{
	scanner->start = line;
	scanner->current = line;
}

static t_token	make_token(int type, t_scanner scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner.start;
	token.length = (int)(scanner.current - scanner.start);
	return (token);
}

static t_token	scan_word(t_scanner *scanner, int c)
{
	int	state;

	state = WORD_STATE;
	if (c == '"')
		state = DOUBLE_QUOTE_STATE;
	else if (c == '\'')
		state = QUOTE_STATE;
	while (*scanner->current != '\0')
	{
		if (state == WORD_STATE)
		{
			if (is_meta(*scanner->current))
				break ;
			else if (*scanner->current == '\'')
				state = QUOTE_STATE;
			else if (*scanner->current == '"')
				state = DOUBLE_QUOTE_STATE;
		}
		else if (state == QUOTE_STATE && *scanner->current == '\'')
			state = WORD_STATE;
		if (state == DOUBLE_QUOTE_STATE && *scanner->current == '"')
			state = WORD_STATE;
		scanner->current++;
	}
	return (make_token(WORD_TOKEN, *scanner));
}

static int	get_token_type(int c, t_scanner *scanner)
{
	if (c == '<' && *scanner->current == '<')
		return (LESS_LESS_TOKEN);
	else if (c == '>' && *scanner->current == '>')
		return (MORE_MORE_TOKEN);
	else if (c == '|' && *scanner->current == '|')
		return (OR_TOKEN);
	else if (c == '&' && *scanner->current == '&')
		return (AND_TOKEN);
	else if (c == '<')
		return (LESS_TOKEN);
	else if (c == '>')
		return (MORE_TOKEN);
	else if (c == '|')
		return (PIPE_TOKEN);
	else
		return (WORD_TOKEN);
}

t_token	scan_token(t_scanner *scanner)
{
	int	type;
	int	c;

	skip_blanks(scanner);
	if (*scanner->current == '\0')
		return (make_token(EOF_TOKEN, *scanner));
	scanner->start = scanner->current;
	c = advance(scanner);
	type = get_token_type(c, scanner);
	if (type == WORD_TOKEN)
		return (scan_word(scanner, c));	
	else if (type == LESS_TOKEN || type == MORE_TOKEN \
		|| type == PIPE_TOKEN)
		return (make_token(type, *scanner));
	else
	{
		advance(scanner);
		return (make_token(type, *scanner));
	}
}
