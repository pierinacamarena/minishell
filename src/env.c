/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 16:43:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/11 16:43:55 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>

typedef struct s_env
{
	char			*content;
	char			*key;
}				t_env;

typedef struct s_env_list
{
	t_env 				*node;
	struct s_env_list	*next;
}				t_env_list;

size_t	ft_strlen(char const *str)
{
	size_t	len;

	len = 0;
	while (str[len] != '\0')
		len++;
	return (len);
}

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


t_env_list *ft_set_node(char *env)
{
    char        **info;
    t_env_list  *list;
	t_env		*node;

    if (!env)
        return (NULL);
	node = malloc(sizeof(t_env));
    info = ft_split(env, '=');
    list->node->key = info[0];
    list->node->content = info[1];
	list->next = NULL;
    return (list);
}

void    ft_add_node(t_env_list **begin, t_env_list *aux)
{
	t_env_list *temp;

	if (*begin == NULL)
		*begin = aux;
	else
	{
		temp = *begin;
		while (temp->next)
		{
			temp = temp->next;
		}
		temp = aux;
	}
}


int main(int ac, char **av, char **env)
{
    int i;
    t_env_list  *begin;
    t_env_list  *aux;

    begin = NULL;
	i = 0;
    while (env[i])
    {
        aux = ft_set_node(env[i]);
        printf("key: %s\n", aux->node->key);
        printf("value: %s\n", aux->node->content);
		ft_add_node(&begin, aux);
        i++;
    }
	return (0);
}