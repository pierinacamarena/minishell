/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcamaren <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:42:45 by pcamaren          #+#    #+#             */
/*   Updated: 2022/07/16 17:42:46 by pcamaren         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// void	ft_remove_expo(t_exp_list **begin, char *value)
// {
// 	t_exp_list	*to_remove;
// 	t_exp_list	*curr;

// 	if (*begin == NULL)
// 		return ;
// 	if (ft_strcmp((*begin)->content, value) == 0)
// 	{
// 		to_remove = *begin;
// 		*begin = (*begin)->next;
// 		free(to_remove->content);
// 		free(to_remove);
// 		return ;
// 	}
// 	curr = *begin;
// 	while (curr->next != NULL)
// 	{
// 		if (ft_strcmp(curr->next->content, value) == 0)
// 		{
// 			to_remove = curr->next;
// 			curr->next = cur->next->next;
// 			free(to_remove->content);
// 			free(to_remove);
// 			return ;
// 		}
// 		curr = curr->next;
// 	}
// }

void	ft_remove_var(t_env_list **begin, char *value)
{
	t_env_list	*to_remove;
	t_env_list	*curr;

	if (*begin == NULL)
	{
		printf("NULL\n");
		return ;
	}
	else if (ft_strcmp((*begin)->node->key, value) == 0)
	{
		printf("begin\n");
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
		printf("inside the loop\n");
		if (ft_strcmp(curr->next->node->key, value) == 0)
		{
			printf("found the value\n");
			to_remove = curr->next;
			curr->next = curr->next->next;
			free(to_remove->node->key);
			free(to_remove->node->content);
			free(to_remove->node);
			free(to_remove);
			return ;
		}
		curr = curr->next;
	}
}

void     ft_unset(t_shell *shell)
{
	int	i;

    if (array_size(shell->cmds) == 1)
    {
        printf("unset: not enough arguments\n");
        return ;
    }
    else
    {
		i = 1;
		while (shell->cmds[i])
		{
			if (ft_strchr(shell->cmds[i], '='))
			{
				printf("unset: %s: invalid parameter name\n", shell->cmds[i]);
				i++;
			}
			if (shell->cmds[i])
			{
				ft_remove_var(&shell->env, shell->cmds[i]);
				ft_print_list(shell->env);
				i++;
			}
		}
    }
}