#include "expand.h"

/*	BAD CASES:
	
	echo "$'HOME'" --> skips the dollar sign
	< $TEST cmd (where $TEST="arg1 arg2") --> ambiguous redirect
*/

char	*expand_parameters(t_token token)
{
	char	buf[BUFSIZE];
	char	*param;
	char	c;
	int		i;
	int		state;
	int		start;

	state = WORD_STATE;
	buf[0] = '\0';
	i = 0;
	while (i < token.length)
	{
		c = token.start[i];
		if (c == '$' && state != QUOTE_STATE)
		{
			start = ++i;
			c = token.start[i];
			while (c != '"' && c != '\'' && i < token.length)
				c = token.start[++i];
			param = strndup(&token.start[start], i - start);
			if (param == NULL)
				return (NULL);
			if (getenv(param) != NULL)
				strcat(buf, getenv(param));
		}
		else if (state == WORD_STATE)
		{
			if (c == '"')
				state = DOUBLE_QUOTE_STATE;
			else if (c == '\'')
				state = QUOTE_STATE;
		}
		else if (state == QUOTE_STATE)
		{
			if (c == '\'')
				state = WORD_STATE;
		}
		else if (state == DOUBLE_QUOTE_STATE)
		{
			if (c == '"')
				state = DOUBLE_QUOTE_STATE;
		}
		strncat(buf, &c, 1);
		i++;
	}
	return (strdup(buf));
}

static int	peek(t_scanner scanner)
{
	return (*scanner.current);
}

static char	*getword(t_scanner *scanner)
{
	int	c;

	skip_blanks(scanner);
	scanner->start = scanner->current;
	if (*scanner->start == '\0')
		return (NULL);
	c = advance(scanner);
	if (c == '"')
	{
		scanner->start = scanner->current;
		c = advance(scanner);
		while (c != '"')
			c = advance(scanner);
		return (strndup(scanner->start, scanner->current - scanner->start - 1));
	}
	else if (c == '\'')
	{
		scanner->start = scanner->current;
		c = advance(scanner);
		while (c != '\'')
			c = advance(scanner);
		return (strndup(scanner->start, scanner->current - scanner->start - 1));
	}
	else
	{
		while (peek(*scanner) != '\0' && peek(*scanner) != '"' && peek(*scanner) != '\'' && !isblank(peek(*scanner)))
			c = advance(scanner);
		return (strndup(scanner->start, scanner->current - scanner->start));
	}
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

static t_elem	*split_words(t_elem *elem)
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
			elem_list->words = strndup(token.start, token.length);
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
