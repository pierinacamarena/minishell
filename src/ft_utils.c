/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 17:46:18 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/06 17:46:21 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	const unsigned char	*p1;
	const unsigned char	*p2;
	unsigned char		c1;
	unsigned char		c2;

	p1 = (const unsigned char *)s1;
	p2 = (const unsigned char *)s2;
	c1 = *p1;
	c2 = *p2;
	while (c1 == c2)
	{
		c1 = (unsigned char)*p1++;
		c2 = (unsigned char)*p2++;
		if (c1 == '\0')
			return (c1 - c2);
	}
	return (c1 - c2);
}

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

char	*ft_strdup(char const *str)
{
	char	*strdup;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str);
	strdup = (char *)malloc(sizeof(char) * len + 1);
	if (!strdup)
		return (NULL);
	while (str[++i])
		strdup[i] = str[i];
	strdup[i] = '\0';
	return (strdup);
}

char	*ft_strchr(char const *str, int c)
{
	while (*str != '\0' && *str != (char)c)
	{
		str++;
		if (*str == (char)c)
			return ((char *)str);
	}
	if (*str == (char)c)
		return ((char *)str);
	return (NULL);
}

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	char	*substr;
	int		i;

	i = 0;
	if (str == NULL)
		return (NULL);
	if (start > ft_strlen(str))
		return (ft_strdup(""));
	substr = (char *)malloc(sizeof(char) * len + 1);
	if (!substr)
		return (NULL);
	while (str[start + i] && len--)
	{
		substr[i] = str[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

void	ft_strdel(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}