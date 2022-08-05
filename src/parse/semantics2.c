/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semantics2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:54:10 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 18:54:17 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*new_words_list(t_elem *words_list, t_elem *elem)
{
	if (words_list == NULL)
		words_list = split_words(elem);
	else
		words_list->next = new_words_list(words_list->next, elem);
	return (words_list);
}

t_elem	*new_elem(t_elem *elem_list, t_token token, int type, t_shell *shell)
{
	if (elem_list == NULL)
	{
		elem_list = (t_elem *)malloc(sizeof(t_elem));
		if (elem_list == NULL)
			free_exit(-1, shell, NULL, HIST | ENV);
		elem_list->type = type;
		if (type == HERE_DOC)
			elem_list->words = ft_strndup(token.start, token.length);
		else
			elem_list->words = expand_parameters(token, shell);
		if (elem_list->words == NULL)
			free_exit(-1, shell, NULL, HIST | ENV);
		elem_list->next = NULL;
	}
	else
		elem_list->next = new_elem(elem_list->next, token, type, shell);
	return (elem_list);
}
