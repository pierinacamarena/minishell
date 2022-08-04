#include "../includes/minishell.h"

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
	while (c != '\0')
	{
		state = update_state(state, c);
		if (state == WORD_STATE)
			if (ft_ismeta(c))
				break ;
		c = advance(scanner);
	}
	scanner->current--;
	return (make_token(WORD_TOKEN, *scanner));
}

static int	get_token_type(int c, t_scanner *scanner)
{
	if (c == '<' && peek(*scanner) == '<')
		return (LESS_LESS_TOKEN);
	else if (c == '>' && peek(*scanner) == '>')
		return (MORE_MORE_TOKEN);
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
	if (peek(*scanner) == '\0')
		return (make_token(EOF_TOKEN, *scanner));
	scanner->start = scanner->current;
	c = advance(scanner);
	type = get_token_type(c, scanner);
	if (type == WORD_TOKEN)
		return (scan_word(scanner, c));	
	else if (type != LESS_TOKEN && type != MORE_TOKEN \
		&& type != PIPE_TOKEN)
		advance(scanner);
	return (make_token(type, *scanner));
}
