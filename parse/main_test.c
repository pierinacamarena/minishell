#include "parse.h"

void	print_table(t_token *symtable[])
{
	for (int i = 0; i < HASHSIZE; i++)
	{
		if (symtable[i] == NULL)
			printf("%d _______\n", i + 1);
		else
		{
			printf("%d ", i + 1);
			for (t_token *np = symtable[i]; np != NULL; np = np->next)
				printf("%d %s->", np->tag, np->lexeme);
			printf("\n");
		}
	}
}

int	main(void)
{
	t_token	*symtable[HASHSIZE];
	char	*line;
	FILE	*fstream;
	size_t	n;
	
	for (int i = 0; i < HASHSIZE; i++)
		symtable[i] = NULL;
	fstream = fdopen(0, "r");
	line = NULL;
	n = 0;
	while (getline(&line, &n, fstream) > 0)
	{
		line[strlen(line) - 1] = '\0';
		get_token(symtable, line);
		while (get_token(symtable, NULL) != NULL)
			;
		free(line);
		line = NULL;
	}
	print_table(symtable);
	return (0);
}
