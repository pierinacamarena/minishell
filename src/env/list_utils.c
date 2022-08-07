/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:32:28 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/07 14:52:10 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	find_replace(t_env_list **list, char *key, char *new_content)
{
	t_env_list	*curr;

	if (*list == NULL)
		return ;
	if (!key)
		return ;
	if (!new_content)
		return ;
	curr = *list;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->node->key, key) == 0)
		{
			free(curr->node->content);
			curr->node->content = ft_strdup(new_content);
		}
		curr = curr->next;
	}
}

int	list_size(t_env_list *list)
{
	t_env_list	*curr;
	int			i;

	i = 0;
	if (list == NULL)
		return (-1);
	curr = list;
	while (curr != NULL)
	{	
		i++;
		curr = curr->next;
	}
	return (i);
}

int	key_exists(t_env_list *list, char *var)
{
	char		**var_split;
	char		*temp;
	t_env_list	*curr;

	if (!var)
		return (-1);
	var_split = ft_split(var, '=');
	temp = ft_strjoin(var_split[0], "=");
	free(var_split[0]);
	var_split[0] = temp;
	curr = list;
	while (curr != NULL)
	{
		if (var_split[0] && curr->node->key && \
		ft_strcmp(curr->node->key, var_split[0]) == 0)
		{
			ft_free(var_split);
			return (1);
		}
		curr = curr->next;
	}
	ft_free(var_split);
	return (0);
}

char	*ft_getenv(t_env_list *begin, char *key)
{
	char		*value;
	t_env_list	*curr;

	if (begin == NULL)
		return (NULL);
	curr = begin;
	value = ft_strjoin(key, "=");
	if (value == NULL)
		free_exit(-1, NULL, NULL, 0);
	while (curr != NULL)
	{
		if (ft_strcmp(curr->node->key, value) == 0)
		{
			free(value);
			return (curr->node->content);
		}
		curr = curr->next;
	}
	free(value);
	return (NULL);
}

int	same_value(t_env_list *list, char *var)
{
	char		*info_one;
	char		*info_two;
	int			i;

	i = 0;
	if (list == NULL)
		return (0);
	if (!var)
		return (-1);
	while (var[i] != '=')
		i++;
	info_one = ft_substr(var, 0, i + 1);
	info_two = ft_substr(var, i + 1, ft_strlen(var));
	i = same_value_helper(list, info_one, info_two);
	free(info_one);
	free(info_two);
	return (i);
}
