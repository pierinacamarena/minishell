/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbourdil <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 14:20:36 by rbourdil          #+#    #+#             */
/*   Updated: 2022/08/06 13:14:07 by rbourdil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_words(const char *s, char c)
{
	int	state;
	int	words;

	state = 0;
	words = 0;
	while (*s != '\0')
	{
		if (*s == c)
			state = 0;
		else if (state == 0)
		{
			state = 1;
			words++;
		}
		s++;
	}
	return (words);
}

static int	size_word(const char *s, char c)
{
	int	size;

	size = 0;
	while (s[size] != c && s[size] != '\0')
		size++;
	return (size);
}

static char	*get_word(const char **ptrs, char c)
{
	char	*word;
	char	*ptr_word;
	int		size;

	while (**ptrs == c && **ptrs != '\0')
		(*ptrs)++;
	size = size_word(*ptrs, c);
	word = malloc(sizeof(char) * (size + 1));
	if (word == NULL)
		return (NULL);
	ptr_word = word;
	while (**ptrs != c && **ptrs != '\0')
	{
		*ptr_word = **ptrs;
		(*ptrs)++;
		ptr_word++;
	}
	*ptr_word = '\0';
	return (word);
}

void	ft_clear(char **split_str)
{
	while (*split_str != NULL)
	{
		free(*split_str);
		*split_str = NULL;
		split_str++;
	}
}

char	**ft_split(char const *s, char c)
{
	char	**split_str;
	int		nb_words;
	int		i;

	nb_words = count_words(s, c);
	split_str = malloc(sizeof(char *) * (nb_words + 1));
	if (split_str == NULL)
		return (NULL);
	i = 0;
	while (i < nb_words)
	{
		split_str[i] = get_word(&s, c);
		if (split_str[i] == NULL)
		{
			ft_clear(split_str);
			free(split_str);
			split_str = NULL;
			return (NULL);
		}
		i++;
	}
	split_str[i] = NULL;
	return (split_str);
}
