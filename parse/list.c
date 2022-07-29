#include "list.h"

void	append_elem_list(t_elem *head, t_elem *new_elem)
{
	if (head == NULL)
		return ;
	while (head->next != NULL)
		head = head->next;
	head->next = new_elem;
}

void	free_elem(t_elem *elem)
{
	free(elem->words);
	free(elem);
}

void	free_elem_list(t_elem *elem)
{
	if (elem != NULL)
	{
		free_elem_list(elem->next);
		free_elem(elem);
	}
}

void	print_elem_list(t_elem *head)
{
	char	*s;
	int		type;

	while (head != NULL)
	{
		type = head->type;
		if (type == READ_FILE)
			s = strdup("READ_FILE");
		else if (type == WRITE_FILE)
			s = strdup("WRITE_FILE");
		else if (type == HERE_DOC)
			s = strdup("HERE_DOC");
		else if (type == APPEND_FILE)
			s = strdup("APPEND_FILE");
		else if (type == SIMPLE_WORD)
			s = strdup("SIMPLE_WORD");
		else
			fprintf(stderr, "unrecognized type\n");
		printf("%s\t%s\n", s, head->words);
		free(s);
		head = head->next;
	}
}

void	print_commands_list(t_pipeline *head)
{
	while (head != NULL)
	{
		printf("|| COMMAND ||\n");
		print_elem_list(head->command);
		head = head->next;
	}
}
