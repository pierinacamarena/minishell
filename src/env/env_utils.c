/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/06 20:25:52 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 20:28:39 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_env_list	*set_node_helper(t_env_list *list, t_env *node_env, \
	char *info_one, char *info_two)
{
	list->node = node_env;
	list->node->key = ft_strdup(info_one);
	if (info_two)
		list->node->content = ft_strdup(info_two);
	else
		list->node->content = NULL;
	list->next = NULL;
	return (list);
}

/*
Function that splits the content of the current array inside
char **env. It splits it at the "=" and assigns that to a node
of the list and returns it.
*/

t_env_list	*ft_set_node(char *env)
{
	char		*info_one;
	char		*info_two;
	int			i;
	t_env_list	*list;
	t_env		*node_env;

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
	set_node_helper(list, node_env, info_one, info_two);
	free(info_one);
	free(info_two);
	return (list);
}
