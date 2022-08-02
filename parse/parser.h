#ifndef PARSER_H
#define PARSER_H

#include <stdio.h>
#include <stdlib.h>

#include "semantics.h"
#include "scanner.h"
#include "lexer.h"
#include "expand.h"
#include "list.h"

#define PANIC_MODE 1
#define REGULAR_MODE 0

int	parse(t_scanner *scanner, t_shell *shell);

#endif
