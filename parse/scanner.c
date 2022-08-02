#include "../includes/minishell.h"

void	skip_blanks(t_scanner *scanner)
{
	while (peek(*scanner) != '\0' && ft_isblank(peek(*scanner)))
		advance(scanner);
}

int	advance(t_scanner *scanner)
{
	int	c;

	c = *scanner->current;
	scanner->current++;
	return (c);
}

int	peek(t_scanner scanner)
{
	return (*scanner.current);
}

void	init_scanner(t_scanner *scanner, const char *line)
{
	scanner->start = line;
	scanner->current = line;
}
