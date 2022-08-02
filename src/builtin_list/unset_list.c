/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:25 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/02 01:37:10 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function that removes the node that contains the key we are looking for
*/

void	ft_remove_var_list(t_env_list **begin, char *value)
{
	t_env_list	*to_remove;
	t_env_list	*curr;
	char		*new_val;
	
	new_val = ft_strjoin(value, "=");
	if (*begin == NULL)
	{
		return ;
	}
	else if (ft_strcmp((*begin)->node->key, new_val) == 0)
	{
		to_remove = *begin;
		*begin = (*begin)->next;
		free(to_remove->node->key);
		free(to_remove->node->content);
		free(to_remove->node);
		free(to_remove);
		return ;
	}
	curr = *begin;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->node->key, new_val) == 0)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove->node->key);
			free(to_remove->node->content);
			free(to_remove->node);
			free(to_remove);
			free(new_val);
			return ;
		}
		curr = curr->next;
	}
}

void     ft_unset_list(t_shell *shell, t_list *data)
{
	int	i;

    if (array_size(data->args) == 1)
    {
		write_error("unset: not enough arguments");
        return ;
    }
    else
    {
		i = 1;
		while (data->args[i])
		{
			if (ft_strchr(data->args[i], '='))
			{
				ft_putstr_fd("unset: ", 2);
				ft_putstr_fd(data->args[i], 2);
				ft_putstr_fd(": invalid parameter name\n", 2);
				i++;
			}
			if (data->args[i])
			{
				ft_remove_var_list(&shell->env, data->args[i]);
				ft_remove_var_list(&shell->exp, data->args[i]);
				i++;
			}
		}
    }
}