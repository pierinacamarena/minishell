#ifndef EXPAND_H
#define EXPAND_H

#include "definitions.h"
#include "include.h"
#include "struct.h"

#include "scanner.h"

t_elem		*new_elem(t_elem *elem_list, t_token token, int type);
t_elem		*new_words_list(t_elem *words_list, t_elem *elem_list);
t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list);

#endif
