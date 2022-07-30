#include "semantics.h"

t_elem	*new_words_list(t_elem *words_list, t_elem *elem)
{
	if (words_list == NULL)
		words_list = split_words(elem);
	else
		words_list->next = new_words_list(words_list->next, elem);
	return (words_list);
}

t_elem	*new_elem(t_elem *elem_list, t_token token, int type)
{
	if (elem_list == NULL)
	{
		elem_list = (t_elem *)malloc(sizeof(t_elem));
		if (elem_list == NULL)
			return (NULL);
		elem_list->type = type;
		if (type == HERE_DOC)
			elem_list->words = ft_strndup(token.start, token.length);
		else
			elem_list->words = expand_parameters(token);
		elem_list->next = NULL;
	}
	else
		elem_list->next = new_elem(elem_list->next, token, type);
	return (elem_list);
}

static char	**get_command(t_elem *words_list)
{
	char	**command;
	char	*command_part;
	t_elem	*pnode;
	int		i;

	i = 0;
	pnode = words_list;
	while (pnode != NULL)
	{
		if (pnode->type == SIMPLE_WORD)
			i++;
		pnode = pnode->next;
	}
	command = (char **)malloc(sizeof(char *) * (i + 1));
	if (command == NULL)
		return (NULL);
	i = 0;
	while (words_list != NULL)
	{
		if (words_list->type == SIMPLE_WORD)
		{
			command_part = ft_strdup(words_list->words);
			if (command_part == NULL)
			{
				//free the command
				return (NULL);
			}
			command[i++] = command_part;
		}
		words_list = words_list->next;
	}
	command[i] = NULL;
	return (command);
}

//arrange so that when there are no redirections, the return value is not NULL
static t_elem	*get_redirections(t_elem *words_list)
{
	t_elem	*head;
	t_elem	*new_elem;

	head = NULL;
	while (words_list != NULL)
	{
		if (words_list->type != SIMPLE_WORD)
		{
			new_elem = copy_elem(words_list);
			if (new_elem == NULL)
			{
				//free previous nodes
				return (NULL);
			}
			head = add_elem_to_list(head, new_elem);
		}
		words_list = words_list->next;
	}
	return (head);
}

t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list)
{
	if (commands_list == NULL)
	{
		commands_list = (t_pipeline *)malloc(sizeof(t_pipeline));
		if (commands_list == NULL)
			return (NULL);
		commands_list->command = get_command(words_list);
		commands_list->redirections = get_redirections(words_list);
		if (commands_list->command == NULL) //add redirs condition
			return (NULL);
		commands_list->next = NULL;
	}
	else
		commands_list->next = new_command(commands_list->next, words_list);
	return (commands_list);
}
