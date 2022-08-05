/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:03:26 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 17:33:58 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*	BAD CASES:
	
	< $TEST cmd (where $TEST="arg1 arg2") --> ambiguous redirect
*/

static void	getval(char *key, t_buffer *buf, t_shell *shell)
{
	char	*val;

	if (ft_strcmp(key, "?") == 0)
	{
		val = ft_itoa(g_exit_code);
		if (val == NULL)
			free_exit(-1, shell, NULL, HIST | ENV); 
		add_str_to_buffer(buf, val);
		free(val);
	}
	else
	{
		val = ft_getenv(shell->env, key);
		add_str_to_buffer(buf, val);
	}
}

static void	parexp(t_scanner scanner, t_buffer *buf, int state, t_shell *shell)
{
	char	*tmp;

	if (state == WORD_STATE && \
	(*scanner.start == '\0' || *scanner.start == '$'))
		add_char_to_buffer(buf, '$');
	else if (state == DOUBLE_QUOTE_STATE && \
	(*scanner.start == '"' || *scanner.start == '\'' || *scanner.start == '$'))
		add_char_to_buffer(buf, '$');
	else
	{
		tmp = ft_strndup(scanner.start, (int)(scanner.current - scanner.start));
		if (tmp == NULL)
			free_exit(-1, shell, NULL, HIST | ENV);
		getval(tmp, buf, shell);
		free(tmp);
	}
}

char	*expand_parameters(t_token token, t_shell *shell)
{
	t_scanner	scanner;
	t_buffer	buffer;
	int			c;
	int			state;

	init_scanner(&scanner, token.start);
	init_buffer(&buffer);
	state = WORD_STATE;
	while (token.length-- > 0)
	{
		c = advance(&scanner);
		state = update_state(state, c);
		if (state != QUOTE_STATE && c == '$')
		{
			scanner.start = scanner.current;
			if (peek(scanner) == '?')
				c = advance(&scanner);
			while (ft_isalnum(peek(scanner)) && token.length-- > 0)
				c = advance(&scanner);
			parexp(scanner, &buffer, state, shell);
		}
		else
			add_char_to_buffer(&buffer, c);
	}
	return (collect_and_clear(&buffer));
}

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

t_elem	*split_words(t_elem *elem)
{
	t_elem		*words_list;
	t_scanner	scanner;
	char		*word;

	init_scanner(&scanner, elem->words);
	word = getword(&scanner);
	words_list = NULL;
	while (word != NULL)
	{
		words_list = new_word(words_list, word, elem->type);
		word = getword(&scanner);
	}
	return (words_list);
}
