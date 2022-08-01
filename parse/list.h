#ifndef LIST_H
#define LIST_H

#include <stdlib.h>
#include <stdio.h> //remove in the end

#include "string_ops.h"
#include "common_defs.h"
#include "utils.h"

t_elem	*add_elem_to_list(t_elem *head, t_elem *new_elem);
t_elem	*copy_elem(t_elem *src);
void	print_elem_list(t_elem *head);
void	print_commands_list(t_pipeline *commands_list);
void	free_elem(t_elem *elem);
void	free_elem_list(t_elem *elem);
void	free_commands_list(t_pipeline *pipeline);

#endif
