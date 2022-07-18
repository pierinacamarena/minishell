/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
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
    while (curr->next != NULL)
    {
        if (ft_strcmp(curr->node->key, key) == 0)
        {
            free(curr->node->key);
            curr->node->key = ft_strdup(new_content);
        }
        curr = curr->next;
    }
    if (ft_strcmp(curr->node->key, key) == 0)
    {
        free(curr->node->key);
        curr->node->key = ft_strdup(new_content);
    }
}