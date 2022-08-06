/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:25:58 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 22:20:15 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*getword(t_scanner *scanner)
{
	t_buffer	buffer;
	int			state;
	int			c;

	init_buffer(&buffer);
	state = WORD_STATE;
	skip_blanks(scanner);
	scanner->start = scanner->current;
	if (*scanner->start == '\0')
		return (NULL);
	c = advance(scanner);
	while (c != '\0')
	{
		state = update_state(state, c);
		if (state == WORD_STATE && ft_isblank(c))
			break ;
		else if ((state == WORD_STATE && c != '"' && c != '\'') \
		|| (state == QUOTE_STATE && c != '\'') \
		|| (state == DOUBLE_QUOTE_STATE && c != '"'))
			add_char_to_buffer(&buffer, c);
		c = advance(scanner);
	}
	scanner->current--;
	return (collect_and_clear(&buffer));
}

static t_elem	*new_word(t_elem *words_list, char *word, int type)
{
	if (words_list == NULL)
	{
		words_list = (t_elem *)malloc(sizeof(t_elem));
		if (words_list == NULL)
			return (NULL);
		words_list->words = word;
		words_list->type = type;
		words_list->next = NULL;
	}
	else
		words_list->next = new_word(words_list->next, word, type);
	return (words_list);
}

t_elem	*split_words(t_elem *elem, t_parse *pack)
{
	t_elem		*words_list;
	t_scanner	scanner;
	char		*word;
	int			nb_words;

	init_scanner(&scanner, elem->words);
	word = getword(&scanner);
	words_list = NULL;
	nb_words = 0;
	while (word != NULL)
	{
		nb_words++;
		words_list = new_word(words_list, word, elem->type);
		word = getword(&scanner);
	}
	if (nb_words > 1 && elem->type != SIMPLE_WORD)
	{
		write_error("ambiguous redirect\n");
		*pack->panic = PANIC_MODE;
	}
	return (words_list);
}
