#include "common_defs.h"
#include "include.h"
#include "scanner.h"
#include "parser.h"

void	print_token(t_token token)
{
	if (token.type == LESS_TOKEN)
		printf("%s\t", "LESS_TOKEN");
	else if (token.type == LESS_LESS_TOKEN)
		printf("%s\t", "LESS_LESS_TOKEN");
	else if (token.type == MORE_TOKEN)
		printf("%s\t", "MORE_TOKEN");
	else if (token.type == MORE_MORE_TOKEN)
		printf("%s\t", "MORE_MORE_TOKEN");
	else if (token.type == PIPE_TOKEN)
		printf("%s\t", "PIPE_TOKEN");
	else if (token.type == OR_TOKEN)
		printf("%s\t", "OR_TOKEN");
	else if (token.type == AND_TOKEN)
		printf("%s\t", "AND_TOKEN");
	else if (token.type == WORD_TOKEN)
		printf("%s\t", "WORD_TOKEN");
	printf("'%.*s'\n", token.length, token.start);
}
	
int	main(void)
{
	t_scanner scanner;
	char	*line;
	FILE	*fstream;
	size_t	n;
	
	fstream = fdopen(0, "r");
	line = NULL;
	n = 0;
	while (getline(&line, &n, fstream) > 0)
	{
		line[strlen(line) - 1] = '\0';
		init_scanner(&scanner, line);
		parse(&scanner);
		free(line);
		line = NULL;
		n = 0;
	}
	return (0);
}
