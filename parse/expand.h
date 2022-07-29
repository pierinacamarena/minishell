#ifndef EXPAND_H
#define EXPAND_H

#include "common_defs.h"
#include "include.h"

#include "scanner.h"
#include "str_ops.h"
#include "parser.h"
#include "buffer.h"
#include "lexer.h"

t_elem		*new_elem(t_elem *elem_list, t_token token, int type);
t_elem		*new_words_list(t_elem *words_list, t_elem *elem_list);
t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list);

#endif
