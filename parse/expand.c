#include "expand.h"

/*	BAD CASES:
	
	< $TEST cmd (where $TEST="arg1 arg2") --> ambiguous redirect
*/

static char	*expand_env_var(char *beg, int len)
{
	char	*expanded;
	char	*tmp;

	if (*beg == '$')
	{
		beg++;
		len--;
	}
	if (len == 0)
		return (strdup("$"));	
	tmp = strndup(beg, len);
	if (tmp == NULL)
		return (NULL);
	if (getenv(tmp) == NULL)
		return (strdup(""));
	else
		expanded = strdup(getenv(tmp));
	return (expanded);
}

static char	*replace(char *beg, char *current, char *var_end)
{
	char	*left;
	char	*mid;
	char	*right;

	left = strndup(beg, current - beg);
	if (left == NULL)
		return (NULL);
	mid = expand_env_var(current, var_end - current);
	if (mid == NULL)
		return (NULL);
	right = strdup(var_end);
	if (right == NULL)
		return (NULL);
	free(beg);
	left = append_str(left, mid);
	free(mid);
	left = append_str(left, right);
	free(right);
	return (left);
}

char	*expand_parameters(t_token token)
{
	char	*beg;
	char	*current;
	char	*var_end;
	int		state;
	int		offset;

	beg = strndup(token.start, token.length);
	if (beg == NULL)
		return (NULL);
	current = beg;
	state = WORD_STATE;
	while (*current != '\0')
	{
		state = update_state(state, *current);
		if (*current == '$' && state != QUOTE_STATE)
		{
			var_end = current + 1;
			while (*var_end != '"' && *var_end != '\'' \
				&& *var_end != '$' && *var_end != '\0')
				var_end++;
			offset = (int)(var_end - beg);
			beg = replace(beg, current, var_end);
			current = beg + offset;
		}
		else
			current++;
	}
	return (beg);
}

static char	*getword(t_scanner *scanner)
{
	t_buffer	buffer;
	char		*ret;
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
		if (state == WORD_STATE)
		{
			if (c == '"')
				state = DOUBLE_QUOTE_STATE;
			else if (c == '\'')
				state = QUOTE_STATE;
			else if (isblank(c))
				break ;
			else
				add_char_to_buffer(&buffer, c);
		}
		else if (state == QUOTE_STATE)
		{
			if (c == '\'')
				state = WORD_STATE;
			else
				add_char_to_buffer(&buffer, c);
		}
		else if (state == DOUBLE_QUOTE_STATE)
		{
			if (c == '"')
				state = WORD_STATE;
			else
				add_char_to_buffer(&buffer, c);
		}
		c = advance(scanner);
	}
	scanner->current--;
	ret = collect(&buffer);
	clear_buffer(&buffer);
	return (ret);
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
