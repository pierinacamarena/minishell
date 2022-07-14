#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* symbol table definitions */

#define HASHSIZE 101

/* tokenizer definitions */

#define OPERATOR 256
#define WORD 257
#define BUFSIZE 4096

/* struct definitions */

typedef struct	s_token {
	int				tag;
	char			*lexeme;
	struct s_token	*next;
}	t_token;

t_token	*get_token(t_token *symtable[], char *line);

t_token	*install(t_token *symtable[], int tag, char *s);

char	*strnjoin(char *s1, char *s2, unsigned int n);

#endif
