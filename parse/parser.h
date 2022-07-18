#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include "scanner.h"

/*	parser definitions */

#define READ_FILE 256
#define WRITE_FILE 257
#define HERE_DOC 258
#define APPEND_FILE 259

int	parse(t_scanner *scanner);

#endif
