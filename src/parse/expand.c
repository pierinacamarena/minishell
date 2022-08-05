/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 17:03:26 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/05 18:14:21 by rbourdil         ###   ########.fr       */
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