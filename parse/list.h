#ifndef LIST_H
#define LIST_H

#include "common_defs.h"
#include "include.h"

void	append_elem_list(t_elem *head, t_elem *new_elem);
void	print_elem_list(t_elem *head);
void	print_commands_list(t_pipeline *commands_list);
void	free_elem(t_elem *elem);
void	free_elem_list(t_elem *elem);

#endif
