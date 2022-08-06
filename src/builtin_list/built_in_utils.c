/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:33:13 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 20:33:35 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*setnode_helper_export(t_env_list *list, t_env *node_env, \
	char *info_one, char *info_two)
{
	list->node = node_env;
	list->node->key = ft_strdup(info_one);
	if (!info_two)
		list->node->content = NULL;
	else
		list->node->content = ft_strdup(info_two);
	list->next = NULL;
	return (list);
}

t_env_list	*ft_set_node_export(char *env)
{
	char		*info_one;
	char		*info_two;
	t_env_list	*list;
	t_env		*node_env;
	int			i;

	i = 0;
	if (!env)
		return (NULL);
	while (env[i] != '=')
		i++;
	info_one = ft_substr(env, 0, i + 1);
	info_two = ft_substr(env, i + 1, ft_strlen(env));
	list = malloc(sizeof(t_env_list));
	if (!list)
		return (NULL);
	node_env = malloc(sizeof(t_env));
	if (!node_env)
		return (NULL);
	setnode_helper_export(list, node_env, info_one, info_two);
	free(info_one);
	free(info_two);
	return (list);
}

void	add_var_list(t_env_list **begin, char *var)
{
	t_env_list	*curr;
	t_env_list	*new;

	new = ft_set_node_export(var);
	if (*begin == NULL)
	{
		*begin = new;
		return ;
	}
	else
	{
		curr = *begin;
		while (curr->next != NULL)
			curr = curr->next;
		curr->next = new;
	}
}

void	split_export(t_shell *shell, char *var)
{
	char	*info_one;
	char	*info_two;
	int		i;

	i = 0;
	while (var[i] != '=')
		i++;
	info_one = ft_substr(var, 0, i + 1);
	info_two = ft_substr(var, i + 1, ft_strlen(var));
	find_replace(&shell->env, info_one, info_two);
	find_replace(&shell->exp, info_one, info_two);
	free(info_one);
	free(info_two);
}

void	export_check_helper(t_shell *shell, char *var)
{
	if (key_exists(shell->env, var) == 0)
	{
		add_var_list(&shell->env, var);
		add_var_list(&shell->exp, var);
		return ;
	}
	else if (key_exists(shell->env, var) == 1)
	{
		if (same_value(shell->env, var) == 0)
		{
			split_export(shell, var);
			return ;
		}
		else if (same_value(shell->env, var) == 1)
			return ;
	}
}
