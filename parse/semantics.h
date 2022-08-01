#ifndef SEMANTICS_H
#define SEMANTICS_H

#include <stdlib.h>

#include "string_ops.h"
#include "expand.h"
#include "common_defs.h"
#include "list.h"

t_elem		*new_words_list(t_elem *words_list, t_elem *elem);
t_elem		*new_elem(t_elem *elem_list, t_token token, int type);
t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list);

#endif
