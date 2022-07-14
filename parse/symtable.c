#include "parse.h"

/* hash function for the symbol table */

static unsigned int	hash(char *s)
{
	unsigned int	hashval;

	hashval = 0;
	while (*s != '\0')
		hashval = *s++ + 31 * hashval;
	return (hashval % HASHSIZE);
}

/* 	looks up a string in the symbol table
	returns a pointer to the location if found or NULL
*/

static t_token	*lookup(t_token *symtable[], char *s)
{
	t_token	*token;

	token = symtable[hash(s)];
	while (token != NULL)
	{
		if (strcmp(s, token->lexeme) == 0)
			return (token);
		token = token->next;
	}
	return (NULL);
}

/*	installs a new token in the symbol table or returns a pointer
	to an existing token if token already exists
*/

t_token	*install(t_token *symtable[], int tag, char *s)
{
	t_token			*token;
	unsigned int	hashval;

	token = lookup(symtable, s);
	if (token == NULL)
	{
		token = (t_token *)malloc(sizeof(t_token));
		if (token == NULL)
			return (NULL);
		token->lexeme = strdup(s);
		if (token->lexeme == NULL)
			return (NULL);
		token->tag = tag;
		hashval = hash(s);
		token->next = symtable[hashval];
		symtable[hashval] = token;
	}
	return (token);
}
