/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 17:31:28 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/11 17:31:36 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_wordcount(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if ((i == 0 && s[i] != c) || (i != 0 && s[i] != c && s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

char	**ft_split(char const *s, char c)
{
	int		j;
    int     i;
    int     len;
	char	**splitstr;

	if (!s)
		return (NULL);
	j = 0;
    i = 0;
    len = 0;
	splitstr = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!splitstr)
		return (NULL);
    while (s[i])
	{
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len)
		{
            splitstr[j] = ft_substr(s, i, len);
            j++;
        }
		if (len)
			i += len;
		else
			i += 1;
		len = 0;
	}
	splitstr[j] = NULL;
	return (splitstr);
}