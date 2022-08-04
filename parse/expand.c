#include "../includes/minishell.h"

/*	BAD CASES:
	
	< $TEST cmd (where $TEST="arg1 arg2") --> ambiguous redirect
*/

static void	add_expanded_param(t_scanner scanner, t_buffer *buffer, int state, t_shell *shell)
{
	int		param_len;
	char	*tmp;
	char	*value;
	int		free_value;

	param_len = (int)(scanner.current - scanner.start);
	if (state == WORD_STATE && \
(*scanner.start == '\0' || *scanner.start == '$'))
		add_char_to_buffer(buffer, '$');
	else if (state == DOUBLE_QUOTE_STATE && \
(*scanner.start == '"' || *scanner.start == '\'' || *scanner.start == '$'))
		add_char_to_buffer(buffer, '$');
	else
	{
		tmp = ft_strndup(scanner.start, param_len);
		if (tmp == NULL)
			return ;
		free_value = 0;
		if (ft_strcmp(tmp, "?") == 0)
		{
			value = ft_itoa(exit_code);
			free_value = 1;
			//clean
			if (value == NULL)
				exit(EXIT_FAILURE);
		}
		else
			value = ft_getenv(shell->env, tmp);
		if (value != NULL)
			add_str_to_buffer(buffer, value);
		if (free_value)
			free(value);
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
			while (peek(scanner) != '\0' && peek(scanner) != '"' \
&& peek(scanner) != '\'' && peek(scanner) != '$' && token.length-- > 0)
				c = advance(&scanner);
			add_expanded_param(scanner, &buffer, state, shell);
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
