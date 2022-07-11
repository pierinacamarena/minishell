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

static char	**helper(char const *s, char **splitstr, char c, int*j)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (s[i])
	{
		while (s[i + len] && s[i + len] != c)
			len++;
		if (len)
			splitstr[*j++] = ft_substr(s, i, len);
		if (len)
			i += len;
		else
			i += 1;
		len = 0;
	}
	return (splitstr);
}

char	**ft_split(char const *s, char c)
{
	int		j;
	char	**splitstr;

	if (!s)
		return (NULL);
	j = 0;
	splitstr = (char **)malloc(sizeof(char *) * (ft_wordcount(s, c) + 1));
	if (!splitstr)
		return (NULL);
	splitstr = helper(s, splitstr, c, &j);
	splitstr[j] = NULL;
	return (splitstr);
}
