/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <pcamaren@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 23:40:25 by pcamaren          #+#    #+#             */
/*   Updated: 2022/08/06 22:54:48 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/*
Function that removes the node that contains the key we are looking for
*/

void	free_unset(t_env_list *list)
{
	free(list->node->key);
	free(list->node->content);
	free(list->node);
	free(list);
}

void	ft_remove_helper(t_env_list **begin, char *new_val)
{
	t_env_list	*curr;
	t_env_list	*to_remove;

	curr = *begin;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->node->key, new_val) == 0)
		{
			to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove);
			return ;
		}
		curr = curr->next;
	}
}

void	ft_remove_var_list(t_env_list **begin, char *value)
{
	t_env_list	*to_remove;
	char		*new_val;

	new_val = ft_strjoin(value, "=");
	if (*begin == NULL)
		return ;
	else if (ft_strcmp((*begin)->node->key, new_val) == 0)
	{
		to_remove = *begin;
		*begin = (*begin)->next;
		free(to_remove);
		return ;
	}
	ft_remove_helper(begin, new_val);
	free(new_val);
}

int	unset_error(t_pipeline *data)
{
	if (array_size(data->command) == 1)
		return (0);
	else if (ft_strcmp(data->command[1], "") == 0)
	{
		write_error("unset: `': not a valid identifier\n");
		return (1);
	}
	return (3);
}

int	ft_unset_list(t_shell *shell, t_pipeline *data)
{
	int	i;
	int	error;

	i = unset_error(data);
	if (i != 3)
		return (i);
	error = 0;
	i = 1;
	while (data->command[i])
	{
		if (ft_strchr(data->command[i], '='))
		{
			error = unset_print(data->command[i]);
			i++;
		}
		if (data->command[i])
		{
			ft_remove_var_list(&shell->env, data->command[i]);
			ft_remove_var_list(&shell->exp, data->command[i]);
			i++;
		}
	}
	return (error);
}
