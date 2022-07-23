#ifndef SCANNER_H
#define SCANNER_H

#include "definitions.h"
#include "include.h"
#include "struct.h"

void	init_scanner(t_scanner *scanner, const char *line);
t_token	scan_token(t_scanner *scanner);
int		advance(t_scanner *scanner);
void	skip_blanks(t_scanner *scanner);

#endif
