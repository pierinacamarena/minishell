#include "expand.h"

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
			if (c == '\'')
				state = WORD_STATE;
		else if (state == DOUBLE_QUOTE_STATE)
			if (c == '"')
				state = DOUBLE_QUOTE_STATE;
		strncat(buf, &c, 1);
		i++;
	}
	return (strdup(buf));
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
