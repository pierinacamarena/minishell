/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:24:59 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 18:25:40 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*copy_elem(t_elem *src)
{
	t_elem	*copy;

	copy = (t_elem *)malloc(sizeof(t_elem));
	if (copy == NULL)
		return (NULL);
	copy->words = ft_strdup(src->words);
	if (copy->words == NULL)
	{
		free(copy);
		return (NULL);
	}
	copy->type = src->type;
	copy->next = NULL;
	return (copy);
}

t_elem	*add_elem_to_list(t_elem *head, t_elem *new_elem)
{
	if (head == NULL)
		head = new_elem;
	else
		head->next = add_elem_to_list(head->next, new_elem);
	return (head);
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
		free_double_ptr(commands_list->command);
		free_elem_list(commands_list->redirections);
		free(commands_list);
	}
}

/*
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

void	print_double_ptr(char **ptr)
{
	while (*ptr != NULL)
	{
		printf("%s ", *ptr);
		ptr++;
	}
	printf("\n");
}

void	print_commands_list(t_pipeline *head)
{
	while (head != NULL)
	{
		printf("***COMMAND***\n");
		print_double_ptr(head->command);
		printf("***REDIRECTIONS***\n");
		print_elem_list(head->redirections);
		printf("\n");
		head = head->next;
	}
}
*/
