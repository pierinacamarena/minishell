#include "utils.h"

int	ft_isblank(int c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	ft_ismeta(int c)
{
	if (c == '<' || c == '>' || c == '|' || c == ' ' || c == '\t')
		return (1);
	return (0);
}

int	update_state(int state, int c)
{
	if (state == WORD_STATE)
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
			state = WORD_STATE;
	}
	return (state);
}

void	free_double_ptr(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i] != NULL)
		free(ptr[i++]);
	free(ptr);
}
