#include "list.h"

void	append_elem_list(t_elem *head, t_elem *new_elem)
{
	if (head == NULL)
		return ;
	while (head->next != NULL)
		head = head->next;
	head->next = new_elem;
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
