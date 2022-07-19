/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 19:52:12 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/10 19:52:14 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	single_quota(char *str, char **cmd, t_splitter *split)
{
	split->i++;
	cmd[split->j] = ft_calloc(sizeof(char), ft_len(str, 39, split->i) + 1);
	if (!cmd)
		return ;
	while (str[split->i] != '\0' && str[split->i] != 39)
		cmd[split->j][split->count++] = str[split->i++];
}

void	double_quota(char *str, char **cmd, t_splitter *split)
{
	split->i++;
	cmd[split->j] = ft_calloc(sizeof(char), ft_len(str, 34, split->i) + 1);
	if (!cmd)
		return ;
	while (str[split->i] != '\0' && str[split->i] != 34)
		cmd[split->j][split->count++] = str[split->i++];
}

void	space_case(char *str, char **cmd, t_splitter *split)
{
	cmd[split->j] = ft_calloc(sizeof(char), ft_len(str, ' ', split->i) + 1);
	if (!cmd)
		return ;
	while (str[split->i] != '\0' && str[split->i] != ' ')
		cmd[split->j][split->count++] = str[split->i++];
}

void	word_count(const char *str, int *i, int *count)
{
	if (str[*i] == 39)
	{
		(*i)++;
		while (str[*i] != 39 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else if (str[*i] == 34)
	{
		(*i)++;
		while (str[*i] != 34 && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
	else
	{
		while (str[*i] != ' ' && str[*i] != '\0')
			(*i)++;
		(*count)++;
	}
}

int	ft_count(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ')
			word_count(str, &i, &count);
		if (str[i] == '\0')
			break ;
		else
			i++;
	}
	return (count);
}

int	ft_len(char const *s, char c, int i)
{
	int	len;

	len = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

char	**cmd_malloc(char *str, char **cmd, t_splitter *split)
{
	split->i = 0;
	split->j = 0;
	if (!str)
		return (NULL);
	while (str[split->i] != '\0' && split->j < split->len)
	{
		split->count = 0;
		if (str[split->i] != ' ')
		{
			if (str[split->i] == 39) //single quote
				single_quota(str, cmd, split);
			else if (str[split->i] == 34) //double quote
				double_quota(str, cmd, split);
			else
			{
				space_case(str, cmd, split);
			}
		}
		cmd[split->j][split->count] = '\0';
		split->i++;
		split->j++;
	}
	cmd[split->j] = NULL;
	return (cmd);
}

/*
splits the command
determines how many commands there are
mallocs the required space
and call the function cmd_malloc that will give the resulting char **
*/
char	**cmd_split(const char *str)
{
	t_splitter	split;
	char		**cmd;

	if (str == NULL)
		return (NULL);
	split.len = ft_count(str);
	cmd = ft_calloc(sizeof(char *), split.len + 1);
	if (!cmd)
		return (NULL);
	return (cmd_malloc((char *)str, cmd, &split));
}