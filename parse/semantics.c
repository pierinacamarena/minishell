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

t_pipeline	*new_command(t_pipeline *commands_list, t_elem *words_list)
{
	if (commands_list == NULL)
	{
		commands_list = (t_pipeline *)malloc(sizeof(t_pipeline));
		if (commands_list == NULL)
			return (NULL);
		commands_list->command = words_list;
		commands_list->next = NULL;
	}
	else
		commands_list->next = new_command(commands_list->next, words_list);
	return (commands_list);
}
