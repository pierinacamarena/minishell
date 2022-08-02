#ifndef EXPAND_H
#define EXPAND_H

#include <stdlib.h>

#include "../includes/minishell.h"
#include "string_ops.h"
#include "scanner.h"
#include "lexer.h"
#include "buffer.h"
#include "utils.h"

char	*expand_parameters(t_token token);
t_elem	*split_words(t_elem *elem);

#endif
