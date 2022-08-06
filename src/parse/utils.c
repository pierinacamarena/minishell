/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:26:16 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 20:36:04 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_realloc(char *src, int n)
{
	char	*ret;
	int		i;

	ret = malloc(sizeof(char) * n);
	if (ret == NULL)
		return (NULL);
	if (src == NULL)
		return (ret);
	i = 0;
	while (n-- > 0 && src[i] != '\0')
	{
		ret[i] = src[i];
		i++;
	}
	free(src);
	return (ret);
}
