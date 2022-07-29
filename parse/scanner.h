#ifndef SCANNER_H
#define SCANNER_H

#include "utils.h"

typedef struct	s_scanner {
	const char	*start;
	const char	*current;
}	t_scanner;

void	init_scanner(t_scanner *scanner, const char *line);
int		advance(t_scanner *scanner);
int		peek(t_scanner scanner);
void	skip_blanks(t_scanner *scanner);

#endif
