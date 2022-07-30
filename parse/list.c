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

void	free_commands_list(t_pipeline *commands_list)
{
	if (commands_list != NULL)
	{
		free_commands_list(commands_list->next);
		free_elem_list(commands_list->command);
		free(commands_list);
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
			s = ft_strdup("READ_FILE");
		else if (type == WRITE_FILE)
			s = ft_strdup("WRITE_FILE");
		else if (type == HERE_DOC)
			s = ft_strdup("HERE_DOC");
		else if (type == APPEND_FILE)
			s = ft_strdup("APPEND_FILE");
		else if (type == SIMPLE_WORD)
			s = ft_strdup("SIMPLE_WORD");
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
