#include "scanner.h"

int	is_meta(int c)
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

t_token	make_token(int type, t_scanner scanner)
{
	t_token	token;

	token.type = type;
	token.start = scanner.start;
	token.length = (int)(scanner.current - scanner.start);
	return (token);
}

t_token	scan_word(t_scanner *scanner, int c)
{
	int	state;

	if (c == '"')
		state = DOUBLE_QUOTE_STATE;
	else if (c == '\'')
		state = QUOTE_STATE;
	else
		state = WORD_STATE;
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
		else if (state == QUOTE_STATE)
		{
			if (*scanner->current == '\'')
				state = WORD_STATE;
		}	
		else if (state == DOUBLE_QUOTE_STATE)
		{
			if (*scanner->current == '"')
				state = WORD_STATE;
		}
		scanner->current++;
	}
	return (make_token(WORD_TOKEN, *scanner));
}

t_token	scan_token(t_scanner *scanner)
{
	int	c;

	skip_blanks(scanner);
	if (*scanner->current == '\0')
		return (make_token(EOF_TOKEN, *scanner));
	scanner->start = scanner->current;
	c = advance(scanner);
	if (c == '<' && *scanner->current == '<')
	{
		advance(scanner);
		return (make_token(LESS_LESS_TOKEN, *scanner));
	}
	else if (c == '>' && *scanner->current == '>')
	{
		advance(scanner);
		return (make_token(MORE_MORE_TOKEN, *scanner));
	}
	else if (c == '|' && *scanner->current == '|')
	{
		advance(scanner);
		return (make_token(OR_TOKEN, *scanner));
	}
	else if (c == '&' && *scanner->current == '&')
	{
		advance(scanner);
		return (make_token(AND_TOKEN, *scanner));
	}
	else if (c == '<')
		return (make_token(LESS_TOKEN, *scanner));
	else if (c == '>')
		return (make_token(MORE_TOKEN, *scanner));
	else if (c == '|')
		return (make_token(PIPE_TOKEN, *scanner));
	else
		return (scan_word(scanner, c));
}
