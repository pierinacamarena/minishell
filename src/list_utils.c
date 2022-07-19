/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 21:32:28 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/15 21:32:29 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    find_replace(t_env_list **list, char *key, char *new_content)
{
    t_env_list *curr;

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

int		list_size(t_env_list *list)
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

int     key_exists(t_env_list *list, char *var)
{
    char        **var_split;
    t_env_list  *curr;
    char        *temp;

    if (!var)
        return (-1);
    var_split = ft_split(var, '=');
	temp = ft_strjoin(var_split[0], "=");
	free(var_split[0]);
	var_split[0] = temp;
    curr = list;
    while (curr != NULL)
    {
        if (ft_strcmp(curr->node->key, var_split[0]) == 0)
        {
            ft_free(var_split);
            return (1);
        }
        curr = curr->next;
    }
    ft_free(var_split);
    return (0);
}

int     same_value(t_env_list *list, char *var)
{
    char        **var_split;
    t_env_list  *curr;

    if (list == NULL)
        return (0);
    if (!var)
        return (-1);
    var_split = ft_split(var, '=');
    curr = list;
    while (curr != NULL)
    {
        if (ft_strcmp(curr->node->content, var_split[1]) == 0)
        {
            ft_free(var_split);
            return (1);
        }
        curr = curr->next;
    }
    ft_free(var_split);
    return (0);
}